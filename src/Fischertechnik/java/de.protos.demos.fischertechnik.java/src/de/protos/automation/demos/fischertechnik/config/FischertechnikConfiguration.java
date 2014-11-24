package de.protos.automation.demos.fischertechnik.config;

import java.util.HashMap;


public class FischertechnikConfiguration {

	protected static final int SETUP_NONE = 0;
	protected static final int SETUP_CONTROL = 1;
	protected static final int SETUP_TEST = 2;
	static int currentSetup = SETUP_NONE; 
	
	public static synchronized FischertechnikConfiguration getInstance(){
		if (instance==null){
			instance = new FischertechnikConfiguration();
			instance.setCurrentSetup(SETUP_CONTROL);
			instance.initValues();
		}
		return instance;
	}
	
	private void setCurrentSetup(int setup){
		currentSetup = setup;
	}
	
	public synchronized int getIntValue(String instance_path, String id){
		Integer return_value = valueMap.get(instance_path+"->"+id);
		if (return_value != null){
			return return_value;
		}
		else {
			System.out.println("**** error getIntValue: " + instance_path+"->"+id+" not defined");
			return 0;
		}
	}
	private void initValues(){
		switch (currentSetup){
		case SETUP_CONTROL:
			initValuesForSetupControl();
			break;
		case SETUP_TEST:
			initValuesForSetupTest();
			break;
		default:
			System.out.println("**** error no setup found for currentSetup = " + currentSetup);
			break;
			
		}
	}

	private void initValuesForSetupTest(){
		
	}

	
	private void initValuesForSetupControl(){
		valueMap = new HashMap<String, Integer>();
		
		final int inputOffset = 2; // offset for additional WAGO Module (750-610) -> 2 additional inputs
		
		// LineSource
		valueMap.put("/MachineSystem/subSystem/Controller/SourceSensor1->sensor", 0+inputOffset);
		
		//****************
		//LEBand1
		valueMap.put("/MachineSystem/subSystem/Controller/BeltStation2/InlineStation->processingActive", 0);

		// Band1
		valueMap.put("/MachineSystem/subSystem/Controller/BeltStation2/Belt/BeltDrive->lr", 0);
		valueMap.put("/MachineSystem/subSystem/Controller/BeltStation2/Belt/BeltDrive->start", 1);

		valueMap.put("/MachineSystem/subSystem/Controller/BeltStation2/Belt->sensor", 1+inputOffset);

		//****************
		//PusherStation1
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation3/InlineStation->processingActive", 0);
		// Schieber1/PusherHW/Drive
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation3/Pusher/PusherHW/Drive->lr", 2);
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation3/Pusher/PusherHW/Drive->start", 3);
		//Schieber1/PusherHW
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation3/Pusher/PusherHW->sensorFront", 2+inputOffset);
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation3/Pusher/PusherHW->sensorBack", 3+inputOffset);
		
		//****************
		// ProductionStation1
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation4/InlineStation->processingActive", 1);
		//Band2/Antrieb
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation4/Belt/BeltDrive->lr", 4);
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation4/Belt/BeltDrive->start", 5);
		//Band2/
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation4/Belt->sensor", 4+inputOffset);

		//ProductionStation1/Drive
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation4/ProductionUnit/StationDrive->lr", 6);
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation4/ProductionUnit/StationDrive->start", 7);
		

		//****************
		// ProductionStation1
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation5/InlineStation->processingActive", 1);
		//Band2/Antrieb
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation5/Belt/BeltDrive->lr", 8);
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation5/Belt/BeltDrive->start", 9);
		//Band2/
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation5/Belt->sensor", 5+inputOffset);

		//ProductionStation1/Drive
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation5/ProductionUnit/StationDrive->lr", 10);
		valueMap.put("/MachineSystem/subSystem/Controller/ProductionStation5/ProductionUnit/StationDrive->start", 11);

		//****************
		//PusherStation2
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation6/InlineStation->processingActive", 0);
		// Schieber1/PusherHW/Drive
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation6/Pusher/PusherHW/Drive->lr", 12);
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation6/Pusher/PusherHW/Drive->start", 13);
		//Schieber1/PusherHW
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation6/Pusher/PusherHW->sensorFront", 6+inputOffset);
		valueMap.put("/MachineSystem/subSystem/Controller/PusherStation6/Pusher/PusherHW->sensorBack", 7+inputOffset);
		
		
		//****************
		// LEBand4
		valueMap.put("/MachineSystem/subSystem/Controller/BeltStation7/InlineStation->processingActive", 0);
		// Band4/Antrieb
		valueMap.put("/MachineSystem/subSystem/Controller/BeltStation7/Belt/BeltDrive->lr", 14);
		valueMap.put("/MachineSystem/subSystem/Controller/BeltStation7/Belt/BeltDrive->start", 15);
		//Band4/
		valueMap.put("/MachineSystem/subSystem/Controller/BeltStation7/Belt->sensor", 8+inputOffset);
		
		
	}
	
	private static FischertechnikConfiguration instance = null;
	
	private HashMap<String, Integer> valueMap = null; 
}
