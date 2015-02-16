/**
 * @author generated by eTrice
 *
 * Dispatcher File of Node nodeRef1 with SubSystem main
 * contains a generated message dispatcher (receiveMessage) for each MessageService (Thread)
 */

#include "messaging/etMessageReceiver.h"
#include "debugging/etLogger.h"
#include "debugging/etMSCLogger.h"


/**
 * generated execute function for all cyclic execute calls for the async or datadriven actor instances of thread "PhysicalThread1"
 */
static void MsgDispatcher_PhysicalThread1_poll(void){
	ET_MSC_LOGGER_SYNC_ENTRY("MsgDispatcher_PhysicalThread1", "execute")
	ATimingService_execute((void*)&_HexagonCANDemo_main_timingService);
	ACruiseController_execute((void*)&_HexagonCANDemo_main_cruise);
	APIDController_execute((void*)&_HexagonCANDemo_main_regler);
	ACAN2FlowportAdapter1in1out_execute((void*)&_HexagonCANDemo_main_adapter);
	ET_MSC_LOGGER_SYNC_EXIT
}

/**
 * generated dispatch function for all messages for the thread "PhysicalThread1"
 */
static etBool MsgDispatcher_PhysicalThread1_receiveMessage(const etMessage* msg){
	ET_MSC_LOGGER_SYNC_ENTRY("MsgDispatcher_PhysicalThread1", "receiveMessage")
	switch(msg->address){
	
		case MESSAGESERVICE_ADDRESS:
			if (msg->evtID == etSystemProtocol_IN_poll) {
				MsgDispatcher_PhysicalThread1_poll();
			}
			else
			if (msg->evtID == etSystemProtocol_IN_terminate)
				return ET_FALSE;
			break;
		
		/* interface items of /HexagonCANDemo/main/timingService */
		case 2+BASE_ADDRESS:
			ATimingService_receiveMessage((void*)&_HexagonCANDemo_main_timingService,&_HexagonCANDemo_main_timingService_const.timer.ports[0].port, msg);
		break;
		case 3+BASE_ADDRESS:
			ATimingService_receiveMessage((void*)&_HexagonCANDemo_main_timingService,&_HexagonCANDemo_main_timingService_const.timer.ports[1].port, msg);
		break;
		
		/* interface items of /HexagonCANDemo/main/canSimuDev */
		case 5+BASE_ADDRESS:
			switch (msg->evtID){
				case PTimer_OUT_timeout:
					PTimerConjPort_timeout_receiveHandler((etPort *)&_HexagonCANDemo_main_canSimuDev_const.timer,msg,(void*)&_HexagonCANDemo_main_canSimuDev,ACANSimulationService_receiveMessage);
					break;
				default: ACANSimulationService_receiveMessage((void*)&_HexagonCANDemo_main_canSimuDev,(etPort*)&_HexagonCANDemo_main_canSimuDev_const.timer, msg);
					break;
			}
			break;
		case 6+BASE_ADDRESS:
			ACANSimulationService_receiveMessage((void*)&_HexagonCANDemo_main_canSimuDev,&_HexagonCANDemo_main_canSimuDev_const.canTx.ports[0].port, msg);
		break;
		case 7+BASE_ADDRESS:
			ACANSimulationService_receiveMessage((void*)&_HexagonCANDemo_main_canSimuDev,&_HexagonCANDemo_main_canSimuDev_const.canRx.ports[0].port, msg);
		break;
		case 8+BASE_ADDRESS:
			ACANSimulationService_receiveMessage((void*)&_HexagonCANDemo_main_canSimuDev,&_HexagonCANDemo_main_canSimuDev_const.canRx.ports[1].port, msg);
		break;
		case 9+BASE_ADDRESS:
			ACANSimulationService_receiveMessage((void*)&_HexagonCANDemo_main_canSimuDev,&_HexagonCANDemo_main_canSimuDev_const.canRx.ports[2].port, msg);
		break;
		case 10+BASE_ADDRESS:
			ACANSimulationService_receiveMessage((void*)&_HexagonCANDemo_main_canSimuDev,&_HexagonCANDemo_main_canSimuDev_const.canRx.ports[3].port, msg);
		break;
		case 11+BASE_ADDRESS:
			ACANSimulationService_receiveMessage((void*)&_HexagonCANDemo_main_canSimuDev,&_HexagonCANDemo_main_canSimuDev_const.canRx.ports[4].port, msg);
		break;
		case 12+BASE_ADDRESS:
			ACANSimulationService_receiveMessage((void*)&_HexagonCANDemo_main_canSimuDev,&_HexagonCANDemo_main_canSimuDev_const.canRx.ports[5].port, msg);
		break;
		
		/* interface items of /HexagonCANDemo/main/monitor */
		case 14+BASE_ADDRESS:
			AHexagonCANMonitor_receiveMessage((void*)&_HexagonCANDemo_main_monitor,(etPort*)&_HexagonCANDemo_main_monitor_const.canRxThrottle, msg);
			break;
		case 15+BASE_ADDRESS:
			AHexagonCANMonitor_receiveMessage((void*)&_HexagonCANDemo_main_monitor,(etPort*)&_HexagonCANDemo_main_monitor_const.canRxSpeed, msg);
			break;
		case 16+BASE_ADDRESS:
			AHexagonCANMonitor_receiveMessage((void*)&_HexagonCANDemo_main_monitor,(etPort*)&_HexagonCANDemo_main_monitor_const.canRxControl, msg);
			break;
		
		/* interface items of /HexagonCANDemo/main/cruise */
		case 18+BASE_ADDRESS:
			ACruiseController_receiveMessage((void*)&_HexagonCANDemo_main_cruise,(etPort*)&_HexagonCANDemo_main_cruise_const.ctrl, msg);
			break;
		case 20+BASE_ADDRESS:
			ACruiseController_receiveMessage((void*)&_HexagonCANDemo_main_cruise,(etPort*)&_HexagonCANDemo_main_cruise_const.canRxCtrl, msg);
			break;
		case 21+BASE_ADDRESS:
			ACruiseController_receiveMessage((void*)&_HexagonCANDemo_main_cruise,(etPort*)&_HexagonCANDemo_main_cruise_const.canRxNominalSpeed, msg);
			break;
		
		/* interface items of /HexagonCANDemo/main/regler */
		case 23+BASE_ADDRESS:
			APIDController_receiveMessage((void*)&_HexagonCANDemo_main_regler,(etPort*)&_HexagonCANDemo_main_regler_const.ctrl, msg);
			break;
		case 27+BASE_ADDRESS:
			APIDController_receiveMessage((void*)&_HexagonCANDemo_main_regler,(etPort*)&_HexagonCANDemo_main_regler_const.pTick, msg);
			break;
		case 28+BASE_ADDRESS:
			switch (msg->evtID){
				case PTimer_OUT_timeout:
					PTimerConjPort_timeout_receiveHandler((etPort *)&_HexagonCANDemo_main_regler_const.timer,msg,(void*)&_HexagonCANDemo_main_regler,APIDController_receiveMessage);
					break;
				default: APIDController_receiveMessage((void*)&_HexagonCANDemo_main_regler,(etPort*)&_HexagonCANDemo_main_regler_const.timer, msg);
					break;
			}
			break;
		
		/* interface items of /HexagonCANDemo/main/adapter */
		case 32+BASE_ADDRESS:
			ACAN2FlowportAdapter1in1out_receiveMessage((void*)&_HexagonCANDemo_main_adapter,(etPort*)&_HexagonCANDemo_main_adapter_const.pTick, msg);
			break;
		case 33+BASE_ADDRESS:
			ACAN2FlowportAdapter1in1out_receiveMessage((void*)&_HexagonCANDemo_main_adapter,(etPort*)&_HexagonCANDemo_main_adapter_const.canRx, msg);
			break;
		case 34+BASE_ADDRESS:
			ACAN2FlowportAdapter1in1out_receiveMessage((void*)&_HexagonCANDemo_main_adapter,(etPort*)&_HexagonCANDemo_main_adapter_const.canTx, msg);
			break;
		
		default:
			etLogger_logErrorF("MessageService_PhysicalThread1_receiveMessage: address %d does not exist ", msg->address);
			break;
	}
	ET_MSC_LOGGER_SYNC_EXIT
	return ET_TRUE;
}
