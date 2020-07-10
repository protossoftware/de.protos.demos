package de.protos.automation.io.modbus.jamod.test;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import de.protos.automation.io.modbus.jamod.MonitoredValueArray;

public class MonitoredValueArrayTest {

	@Test
	public void testMonitoredValueArray() {
		MonitoredValueArray mva = new MonitoredValueArray(123);
		assertEquals(123, mva.getSize());
		for (int i=0; i<123; i++){
			assertEquals(false, mva.getValue(i));
			assertEquals(false, mva.hasChanged(i));
		}
	}

	@Test
	public void testSetGetValue() {
		MonitoredValueArray mva = new MonitoredValueArray(123);
		mva.setValue(0, true);
		mva.setValue(50, true);
		mva.setValue(122, true);
		assertEquals(true, mva.getValue(0));
		assertEquals(true, mva.getValue(50));
		assertEquals(true, mva.getValue(122));
	}

	@Test
	public void testGetCurrentValues() {
		MonitoredValueArray mva = new MonitoredValueArray(123);
		mva.setValue(0, true);
		mva.setValue(50, true);
		mva.setValue(122, true);
		assertEquals(true, mva.getValue(0));
		assertEquals(true, mva.getValue(50));
		assertEquals(true, mva.getValue(122));
	}

	@Test
	public void testHasChanged() {
		MonitoredValueArray mva = new MonitoredValueArray(123);
		mva.setValue(0, true);
		mva.setValue(50, true);
		mva.setValue(122, true);
		assertEquals(true, mva.hasChanged(0));
		assertEquals(true, mva.hasChanged(50));
		assertEquals(true, mva.hasChanged(122));

		assertEquals(false, mva.hasChanged(1));
		assertEquals(false, mva.hasChanged(49));
		assertEquals(false, mva.hasChanged(51));
		assertEquals(false, mva.hasChanged(121));
	}

	@Test
	public void testInvalidate() {
		MonitoredValueArray mva = new MonitoredValueArray(123);
		mva.setValue(0, true);
		mva.setValue(50, true);
		mva.setValue(122, true);
		assertEquals(true, mva.hasChanged(0));
		assertEquals(true, mva.hasChanged(50));
		assertEquals(true, mva.hasChanged(122));
		mva.invalidate();
		assertEquals(false, mva.hasChanged(0));
		assertEquals(false, mva.hasChanged(50));
		assertEquals(false, mva.hasChanged(122));
	}

}
