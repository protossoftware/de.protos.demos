package de.protos.automation.io.modbus.jamod;

public class MonitoredValueArray implements IStaticBooleanArray  {
	public MonitoredValueArray(int size){
		this.size = size;
		currentValues = new StaticBooleanArray(size);
		currentValues.setAllValues(false);
		changedValues = new StaticBooleanArray(size);
		changedValues.setAllValues(false);
	}

	@Override
	public void setValue(int index, boolean value) {
		assert(index < 0);
		assert (index >= size);
		if (currentValues.getValue(index)==value){
			// nothing changed
			return;
		}
		else{
			// value changed -> also changedValues has to be updated
			currentValues.setValue(index, value);
			changedValues.setValue(index, true);
		}
	}

	@Override
	public boolean getValue(int index) {
		assert(index < 0);
		assert (index >= size);
		return currentValues.getValue(index);
	}

	public boolean hasChanged(int index) {
		return changedValues.getValue(index);
	}

	public void invalidate(){
		// all changes are set false 
		changedValues.setAllValues(false);
	}

	public int getSize() {
		return size;
	}

	private int size;

	private StaticBooleanArray currentValues = null;


	private StaticBooleanArray changedValues = null;
	
}
