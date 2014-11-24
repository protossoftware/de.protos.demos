package de.protos.automation.io.modbus.jamod;

public class StaticBooleanArray implements IStaticBooleanArray {
	public StaticBooleanArray(int size){
		this.valueList = new boolean[size];
		this.size=size;
	}
	
	public void setAllValues(boolean value){
		for (int i=0; i<size; i++)
			valueList[i]=value;
	}
	
	public int getSize() {
		return size;
	}

	public boolean[] getValueList() {
		return valueList;
	}
	/* (non-Javadoc)
	 * @see de.protos.automation.io.modbus.jamod.IStaticBooleanArray#setValue(int, boolean)
	 */
	@Override
	public void setValue(int index, boolean value) {
		assert(index < 0);
		assert (index >= size);
		valueList[index] = value;
	}
	/* (non-Javadoc)
	 * @see de.protos.automation.io.modbus.jamod.IStaticBooleanArray#getValue(int)
	 */
	@Override
	public boolean getValue(int index) {
		assert(index < 0);
		assert (index >= size);
		return valueList[index];
	}
	
	public void copyDeep(StaticBooleanArray array){
		assert(size != array.getSize());
		for (int i=0; i<size; i++)
			valueList[i]=array.getValue(i);
	}

	private boolean[] valueList = null;
	private int size = 0;

}
