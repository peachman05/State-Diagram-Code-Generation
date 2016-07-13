package org.yakindu.scr.callhandling;
import org.yakindu.scr.IStatemachine;
import org.yakindu.scr.ITimerCallback;

public interface ICallHandlingStatemachine extends ITimerCallback, IStatemachine {
	public interface SCInterface {

	}

	public SCInterface getSCInterface();

	public interface SCIUser {
		public void raiseAccept_call();
		public void raiseDismiss_call();

	}

	public SCIUser getSCIUser();

	public interface SCIPhone {
		public void raiseIncoming_call();
		public long getDuration();
		public void setDuration(long value);

	}

	public SCIPhone getSCIPhone();

}
