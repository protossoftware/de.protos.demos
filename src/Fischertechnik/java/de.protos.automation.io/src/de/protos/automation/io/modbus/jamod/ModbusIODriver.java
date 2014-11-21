package de.protos.automation.io.modbus.jamod;

import java.net.InetAddress;

import net.wimpi.modbus.ModbusException;
import net.wimpi.modbus.facade.ModbusTCPMaster;
import net.wimpi.modbus.util.BitVector;

public class ModbusIODriver {
	
	public ModbusIODriver(InetAddress slaveAddress, int port, int inputRange, int outputRange) {
		super();
		_slaveAddress = slaveAddress;
		_port = port;
		this.inputRange = inputRange;
		inputBuffer = new MonitoredValueArray(inputRange);
		assert(inputBuffer!=null);
		this.outputRange = outputRange;
		outputBuffer = new MonitoredValueArray(outputRange);
		assert(outputBuffer!=null);
	}

	public void connect(){
		try {
				_MBMaster = new ModbusTCPMaster( _slaveAddress.getHostName(),_port);
				_MBMaster.connect();
			}
			catch (Exception ex)
			{
				System.out.println("Connection fail"+ex.getStackTrace());
			}		
	}
	
	public void disconnect(){
		if (_MBMaster != null){
			_MBMaster.disconnect();
			_MBMaster = null;
		}
	}

	public void setOutput(int channel, boolean value) {
		outputBuffer.setValue(channel, value);
	}

	public boolean getOutput(int channel) {
		return outputBuffer.getValue(channel);
	}
	
	public void writeOutputBufferToHW(){
		// writing all outputs from buffer to hardware
		try {
			if (_MBMaster != null) {
				for (int index=0; index<outputRange; index++){
					if (outputBuffer.hasChanged(index))
						_MBMaster.writeCoil(0, index, outputBuffer.getValue(index));
				}
			}
		} catch (ModbusException mex) {
			mex.printStackTrace();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
	
	public void readInputBufferFromHW(){
		try {
			if (_MBMaster != null) {
				BitVector obit = _MBMaster.readCoils(0, inputRange);
				for (int index=0; index<outputRange; index++){
					inputBuffer.setValue(index, obit.getBit(index));
				}
			}
		} catch (ModbusException mex) {
			mex.printStackTrace();
		}
	}

	public boolean getInput(int channel) {
		return inputBuffer.getValue(channel);
	}
	
	public boolean hasInputChanged(int channel) {
		return inputBuffer.hasChanged(channel);
	}

	public void invalidateInputs() {
		inputBuffer.invalidate();
	}
	
	// members for Jamod Driver
	private InetAddress _slaveAddress = null;
	private int _port =502;
	private ModbusTCPMaster _MBMaster = null;

	// members for buffer handling
	private int inputRange = 0;
	private int outputRange = 0;
	private MonitoredValueArray inputBuffer = null;
	private MonitoredValueArray outputBuffer = null;
	


}
