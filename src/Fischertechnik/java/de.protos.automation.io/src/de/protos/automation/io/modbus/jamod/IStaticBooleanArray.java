package de.protos.automation.io.modbus.jamod;

public interface IStaticBooleanArray {

	public abstract void setValue(int index, boolean value);

	public abstract boolean getValue(int index);

}