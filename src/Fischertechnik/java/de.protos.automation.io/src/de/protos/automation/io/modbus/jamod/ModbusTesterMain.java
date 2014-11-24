package de.protos.automation.io.modbus.jamod;

import java.net.InetAddress;
import java.net.UnknownHostException;


public class ModbusTesterMain {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		setOutputGet32InputChannels(31);
	}

	private static void setOutputGet32InputChannels(int channel) {
		ModbusIODriver driver;
		try {
			driver = new ModbusIODriver(InetAddress.getByName("192.168.1.140"), 502, 32, 32);
			driver.connect();
			while(true){
				
				driver.setOutput(channel, true);
				driver.writeOutputBufferToHW();
				driver.readInputBufferFromHW();
				String result = "";
				for (int i=0; i<32; i++){
					if (driver.hasInputChanged(i)){
						result += "1";
					}
					else{
						result += "0";
					}
				}
				System.out.println("Inputs: "+result);
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			// driver.disconnect();
		} catch (UnknownHostException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

}

