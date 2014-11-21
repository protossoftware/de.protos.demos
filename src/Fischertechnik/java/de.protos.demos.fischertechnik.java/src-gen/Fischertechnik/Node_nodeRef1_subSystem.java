package Fischertechnik;

import org.eclipse.etrice.runtime.java.config.IVariableService;
import org.eclipse.etrice.runtime.java.debugging.DebuggingService;
import org.eclipse.etrice.runtime.java.messaging.IRTObject;
import org.eclipse.etrice.runtime.java.messaging.IMessageService;
import org.eclipse.etrice.runtime.java.messaging.MessageService;
import org.eclipse.etrice.runtime.java.messaging.MessageServiceController;
import org.eclipse.etrice.runtime.java.messaging.RTServices;
import org.eclipse.etrice.runtime.java.modelbase.ActorClassBase;
import org.eclipse.etrice.runtime.java.modelbase.DataPortBase;
import org.eclipse.etrice.runtime.java.modelbase.OptionalActorInterfaceBase;
import org.eclipse.etrice.runtime.java.modelbase.IOptionalActorFactory;
import org.eclipse.etrice.runtime.java.modelbase.SubSystemClassBase;
import org.eclipse.etrice.runtime.java.modelbase.InterfaceItemBase;
import org.eclipse.etrice.runtime.java.modelbase.InterfaceItemBroker;

import Actuators.*;
import AutomationProtocols.*;
import GenericLineElements.*;
import protos.automation.service.io.*;
import protos.automation.service.provider.*;
import room.basic.service.timing.*;


public class Node_nodeRef1_subSystem extends SubSystemClassBase {
	
	public static final int THREAD_PHYSICALTHREAD1 = 0;

	
	public Node_nodeRef1_subSystem(IRTObject parent, String name) {
		super(parent, name);
	}
	
	@Override
	public void receiveEvent(InterfaceItemBase ifitem, int evt, Object data){
	}
	
	@Override	
	public void instantiateMessageServices() {
	
		IMessageService msgService;
		msgService = new MessageService(this, MessageService.ExecMode.MIXED, 100000000L, 0, THREAD_PHYSICALTHREAD1, "MessageService_PhysicalThread1" /*, thread_prio */);
		RTServices.getInstance().getMsgSvcCtrl().addMsgSvc(msgService);
	}

	@Override
	public void instantiateActors() {
		
		// thread mappings

		// sub actors
		DebuggingService.getInstance().addMessageActorCreate(this, "Controller");
		new MachineController(this, "Controller"); 
		DebuggingService.getInstance().addMessageActorCreate(this, "services");
		new ServiceProvider(this, "services"); 
		
		// create service brokers in optional actor interfaces
		
		// wiring
		InterfaceItemBase.connect(this, "services/ioService/dig_in", "Controller/SourceSensor1/sensor");
		InterfaceItemBase.connect(this, "services/ioService/dig_in", "Controller/BeltStation2/Belt/sensor");
		InterfaceItemBase.connect(this, "services/ioService/dig_in", "Controller/PusherStation3/Pusher/PusherHW/sensorFront");
		InterfaceItemBase.connect(this, "services/ioService/dig_in", "Controller/PusherStation3/Pusher/PusherHW/sensorBack");
		InterfaceItemBase.connect(this, "services/ioService/dig_in", "Controller/ProductionStation4/Belt/sensor");
		InterfaceItemBase.connect(this, "services/ioService/dig_in", "Controller/ProductionStation5/Belt/sensor");
		InterfaceItemBase.connect(this, "services/ioService/dig_in", "Controller/PusherStation6/Pusher/PusherHW/sensorFront");
		InterfaceItemBase.connect(this, "services/ioService/dig_in", "Controller/PusherStation6/Pusher/PusherHW/sensorBack");
		InterfaceItemBase.connect(this, "services/ioService/dig_in", "Controller/BeltStation7/Belt/sensor");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/BeltStation2/Belt/BeltDrive/lr");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/BeltStation2/Belt/BeltDrive/start");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/PusherStation3/Pusher/PusherHW/Drive/lr");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/PusherStation3/Pusher/PusherHW/Drive/start");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/ProductionStation4/Belt/BeltDrive/lr");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/ProductionStation4/Belt/BeltDrive/start");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/ProductionStation4/ProductionUnit/StationDrive/lr");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/ProductionStation4/ProductionUnit/StationDrive/start");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/ProductionStation5/Belt/BeltDrive/lr");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/ProductionStation5/Belt/BeltDrive/start");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/ProductionStation5/ProductionUnit/StationDrive/lr");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/ProductionStation5/ProductionUnit/StationDrive/start");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/PusherStation6/Pusher/PusherHW/Drive/lr");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/PusherStation6/Pusher/PusherHW/Drive/start");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/BeltStation7/Belt/BeltDrive/lr");
		InterfaceItemBase.connect(this, "services/ioService/dig_out", "Controller/BeltStation7/Belt/BeltDrive/start");
		InterfaceItemBase.connect(this, "services/timingService/timer", "Controller/BeltStation2/Belt/timeout");
		InterfaceItemBase.connect(this, "services/timingService/timer", "Controller/PusherStation3/Pusher/PusherHW/timeout");
		InterfaceItemBase.connect(this, "services/timingService/timer", "Controller/ProductionStation4/Belt/timeout");
		InterfaceItemBase.connect(this, "services/timingService/timer", "Controller/ProductionStation4/ProductionUnit/timeout");
		InterfaceItemBase.connect(this, "services/timingService/timer", "Controller/ProductionStation5/Belt/timeout");
		InterfaceItemBase.connect(this, "services/timingService/timer", "Controller/ProductionStation5/ProductionUnit/timeout");
		InterfaceItemBase.connect(this, "services/timingService/timer", "Controller/PusherStation6/Pusher/PusherHW/timeout");
		InterfaceItemBase.connect(this, "services/timingService/timer", "Controller/BeltStation7/Belt/timeout");
		
		// apply instance attribute configurations
	}
	
	@Override
	public void init(){
		DebuggingService.getInstance().addVisibleComment("begin sub system initialization");
		super.init();
		DebuggingService.getInstance().addVisibleComment("done sub system initialization");
	}
		
	@Override
	public void stop(){
		super.stop();
	}
	
	@Override
	public boolean hasGeneratedMSCInstrumentation() {
		return true;
	}
	
	@Override
	public void destroy() {
		DebuggingService.getInstance().addVisibleComment("begin sub system destruction");
		super.destroy();
		DebuggingService.getInstance().addVisibleComment("done sub system destruction");
	}
	
	public IOptionalActorFactory getFactory(String optionalActorClass, String actorClass) {
		
		return null;
	}
};
