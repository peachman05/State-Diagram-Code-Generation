
package org.yakindu.scr;

import org.yakindu.scr.TimerService;
  import org.yakindu.scr.callhandling.CallHandlingStatemachine;

  public class CallHandlingClient {

      public static void main(String[] args) throws InterruptedException {

          // Create the state machine:
          CallHandlingStatemachine sm = new CallHandlingStatemachine();
          sm.setTimer(new TimerService());

          // Initialize the state machine:
          sm.init();

          // Enter the state machine and implicitly activate its "Idle" state:
          sm.enter();

          // Raise an incoming call:
          sm.getSCIPhone().raiseIncoming_call();
          sm.runCycle();

          // Accept the call:
          sm.getSCIUser().raiseAccept_call();
          sm.runCycle();

          // Keep the phone conversation busy for a while:
          for (int i = 0; i < 50; i++) {
              Thread.sleep(200);
              sm.runCycle();
          }

          // Before hang-up, output the duration of the call:
          System.out.println(String.format("The phone call took %d seconds.",
                  sm.getSCIPhone().getDuration()));

          // Hang up the phone:
          sm.getSCIUser().raiseDismiss_call();
          sm.runCycle();
      }
  }