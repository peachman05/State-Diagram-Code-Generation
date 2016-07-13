package org.yakindu.scr.callhandling;
import org.yakindu.scr.ITimer;

public class CallHandlingStatemachine implements ICallHandlingStatemachine {

	protected class SCInterfaceImpl implements SCInterface {

	}

	protected SCInterfaceImpl sCInterface;

	protected class SCIUserImpl implements SCIUser {

		private boolean accept_call;

		public void raiseAccept_call() {
			accept_call = true;
		}

		private boolean dismiss_call;

		public void raiseDismiss_call() {
			dismiss_call = true;
		}

		protected void clearEvents() {
			accept_call = false;
			dismiss_call = false;
		}

	}

	protected SCIUserImpl sCIUser;

	protected class SCIPhoneImpl implements SCIPhone {

		private boolean incoming_call;

		public void raiseIncoming_call() {
			incoming_call = true;
		}

		private long duration;

		public long getDuration() {
			return duration;
		}

		public void setDuration(long value) {
			this.duration = value;
		}

		protected void clearEvents() {
			incoming_call = false;
		}

	}

	protected SCIPhoneImpl sCIPhone;

	private boolean initialized = false;

	public enum State {
		main_region_Idle, main_region_Incoming_Call, main_region_Active_Call, main_region_Dismiss_Call, $NullState$
	};

	private final State[] stateVector = new State[1];

	private int nextStateIndex;

	private ITimer timer;

	private final boolean[] timeEvents = new boolean[2];

	public CallHandlingStatemachine() {

		sCInterface = new SCInterfaceImpl();
		sCIUser = new SCIUserImpl();
		sCIPhone = new SCIPhoneImpl();
	}

	public void init() {
		this.initialized = true;
		if (timer == null) {
			throw new IllegalStateException("timer not set.");
		}
		for (int i = 0; i < 1; i++) {
			stateVector[i] = State.$NullState$;
		}

		clearEvents();
		clearOutEvents();

		sCIPhone.setDuration(0);
	}

	public void enter() {
		if (!initialized)
			throw new IllegalStateException(
					"The state machine needs to be initialized first by calling the init() function.");

		if (timer == null) {
			throw new IllegalStateException("timer not set.");
		}
		enterSequence_main_region_default();
	}

	public void exit() {
		exitSequence_main_region();
	}

	/**
	 * @see IStatemachine#isActive()
	 */
	public boolean isActive() {

		return stateVector[0] != State.$NullState$;
	}

	/** 
	* Always returns 'false' since this state machine can never become final.
	*
	 * @see IStatemachine#isFinal()
	 */
	public boolean isFinal() {
		return false;
	}

	/**
	* This method resets the incoming events (time events included).
	*/
	protected void clearEvents() {
		sCIUser.clearEvents();
		sCIPhone.clearEvents();

		for (int i = 0; i < timeEvents.length; i++) {
			timeEvents[i] = false;
		}
	}

	/**
	* This method resets the outgoing events.
	*/
	protected void clearOutEvents() {
	}

	/**
	* Returns true if the given state is currently active otherwise false.
	*/
	public boolean isStateActive(State state) {
		switch (state) {
			case main_region_Idle :
				return stateVector[0] == State.main_region_Idle;
			case main_region_Incoming_Call :
				return stateVector[0] == State.main_region_Incoming_Call;
			case main_region_Active_Call :
				return stateVector[0] == State.main_region_Active_Call;
			case main_region_Dismiss_Call :
				return stateVector[0] == State.main_region_Dismiss_Call;
			default :
				return false;
		}
	}

	/**
	* Set the {@link ITimer} for the state machine. It must be set
	* externally on a timed state machine before a run cycle can be correct
	* executed.
	* 
	* @param timer
	*/
	public void setTimer(ITimer timer) {
		this.timer = timer;
	}

	/**
	* Returns the currently used timer.
	* 
	* @return {@link ITimer}
	*/
	public ITimer getTimer() {
		return timer;
	}

	public void timeElapsed(int eventID) {
		timeEvents[eventID] = true;
	}

	public SCInterface getSCInterface() {
		return sCInterface;
	}
	public SCIUser getSCIUser() {
		return sCIUser;
	}
	public SCIPhone getSCIPhone() {
		return sCIPhone;
	}

	private boolean check_main_region_Idle_tr0_tr0() {
		return sCIPhone.incoming_call;
	}

	private boolean check_main_region_Incoming_Call_tr0_tr0() {
		return sCIUser.accept_call;
	}

	private boolean check_main_region_Incoming_Call_tr1_tr1() {
		return sCIUser.dismiss_call;
	}

	private boolean check_main_region_Active_Call_tr0_tr0() {
		return sCIUser.dismiss_call;
	}

	private boolean check_main_region_Active_Call_lr0_lr0() {
		return timeEvents[0];
	}

	private boolean check_main_region_Dismiss_Call_tr0_tr0() {
		return timeEvents[1];
	}

	private void effect_main_region_Idle_tr0() {
		exitSequence_main_region_Idle();

		enterSequence_main_region_Incoming_Call_default();
	}

	private void effect_main_region_Incoming_Call_tr0() {
		exitSequence_main_region_Incoming_Call();

		enterSequence_main_region_Active_Call_default();
	}

	private void effect_main_region_Incoming_Call_tr1() {
		exitSequence_main_region_Incoming_Call();

		enterSequence_main_region_Dismiss_Call_default();
	}

	private void effect_main_region_Active_Call_tr0() {
		exitSequence_main_region_Active_Call();

		enterSequence_main_region_Dismiss_Call_default();
	}

	private void effect_main_region_Active_Call_lr0_lr0() {
		sCIPhone.setDuration(sCIPhone.getDuration() + 1);
	}

	private void effect_main_region_Dismiss_Call_tr0() {
		exitSequence_main_region_Dismiss_Call();

		enterSequence_main_region_Idle_default();
	}

	/* Entry action for state 'Active Call'. */
	private void entryAction_main_region_Active_Call() {

		timer.setTimer(this, 0, 1 * 1000, true);
	}

	/* Entry action for state 'Dismiss Call'. */
	private void entryAction_main_region_Dismiss_Call() {

		timer.setTimer(this, 1, 2 * 1000, false);
	}

	/* Exit action for state 'Active Call'. */
	private void exitAction_main_region_Active_Call() {
		timer.unsetTimer(this, 0);
	}

	/* Exit action for state 'Dismiss Call'. */
	private void exitAction_main_region_Dismiss_Call() {
		timer.unsetTimer(this, 1);

		sCIPhone.setDuration(0);
	}

	/* 'default' enter sequence for state Idle */
	private void enterSequence_main_region_Idle_default() {
		nextStateIndex = 0;
		stateVector[0] = State.main_region_Idle;
	}

	/* 'default' enter sequence for state Incoming Call */
	private void enterSequence_main_region_Incoming_Call_default() {
		nextStateIndex = 0;
		stateVector[0] = State.main_region_Incoming_Call;
	}

	/* 'default' enter sequence for state Active Call */
	private void enterSequence_main_region_Active_Call_default() {
		entryAction_main_region_Active_Call();

		nextStateIndex = 0;
		stateVector[0] = State.main_region_Active_Call;
	}

	/* 'default' enter sequence for state Dismiss Call */
	private void enterSequence_main_region_Dismiss_Call_default() {
		entryAction_main_region_Dismiss_Call();

		nextStateIndex = 0;
		stateVector[0] = State.main_region_Dismiss_Call;
	}

	/* 'default' enter sequence for region main region */
	private void enterSequence_main_region_default() {
		react_main_region__entry_Default();
	}

	/* Default exit sequence for state Idle */
	private void exitSequence_main_region_Idle() {
		nextStateIndex = 0;
		stateVector[0] = State.$NullState$;
	}

	/* Default exit sequence for state Incoming Call */
	private void exitSequence_main_region_Incoming_Call() {
		nextStateIndex = 0;
		stateVector[0] = State.$NullState$;
	}

	/* Default exit sequence for state Active Call */
	private void exitSequence_main_region_Active_Call() {
		nextStateIndex = 0;
		stateVector[0] = State.$NullState$;

		exitAction_main_region_Active_Call();
	}

	/* Default exit sequence for state Dismiss Call */
	private void exitSequence_main_region_Dismiss_Call() {
		nextStateIndex = 0;
		stateVector[0] = State.$NullState$;

		exitAction_main_region_Dismiss_Call();
	}

	/* Default exit sequence for region main region */
	private void exitSequence_main_region() {
		switch (stateVector[0]) {
			case main_region_Idle :
				exitSequence_main_region_Idle();
				break;

			case main_region_Incoming_Call :
				exitSequence_main_region_Incoming_Call();
				break;

			case main_region_Active_Call :
				exitSequence_main_region_Active_Call();
				break;

			case main_region_Dismiss_Call :
				exitSequence_main_region_Dismiss_Call();
				break;

			default :
				break;
		}
	}

	/* The reactions of state Idle. */
	private void react_main_region_Idle() {
		if (check_main_region_Idle_tr0_tr0()) {
			effect_main_region_Idle_tr0();
		}
	}

	/* The reactions of state Incoming Call. */
	private void react_main_region_Incoming_Call() {
		if (check_main_region_Incoming_Call_tr0_tr0()) {
			effect_main_region_Incoming_Call_tr0();
		} else {
			if (check_main_region_Incoming_Call_tr1_tr1()) {
				effect_main_region_Incoming_Call_tr1();
			}
		}
	}

	/* The reactions of state Active Call. */
	private void react_main_region_Active_Call() {
		if (check_main_region_Active_Call_tr0_tr0()) {
			effect_main_region_Active_Call_tr0();
		} else {
			if (check_main_region_Active_Call_lr0_lr0()) {
				effect_main_region_Active_Call_lr0_lr0();
			}
		}
	}

	/* The reactions of state Dismiss Call. */
	private void react_main_region_Dismiss_Call() {
		if (check_main_region_Dismiss_Call_tr0_tr0()) {
			effect_main_region_Dismiss_Call_tr0();
		}
	}

	/* Default react sequence for initial entry  */
	private void react_main_region__entry_Default() {
		enterSequence_main_region_Idle_default();
	}

	public void runCycle() {
		if (!initialized)
			throw new IllegalStateException(
					"The state machine needs to be initialized first by calling the init() function.");

		clearOutEvents();

		for (nextStateIndex = 0; nextStateIndex < stateVector.length; nextStateIndex++) {

			switch (stateVector[nextStateIndex]) {
				case main_region_Idle :
					react_main_region_Idle();
					break;
				case main_region_Incoming_Call :
					react_main_region_Incoming_Call();
					break;
				case main_region_Active_Call :
					react_main_region_Active_Call();
					break;
				case main_region_Dismiss_Call :
					react_main_region_Dismiss_Call();
					break;
				default :
					// $NullState$
			}
		}

		clearEvents();
	}
}
