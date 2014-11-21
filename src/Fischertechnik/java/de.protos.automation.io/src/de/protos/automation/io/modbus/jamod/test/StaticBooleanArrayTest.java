package de.protos.automation.io.modbus.jamod.test;

import static org.junit.Assert.*;

import org.junit.Test;

import de.protos.automation.io.modbus.jamod.StaticBooleanArray;

public class StaticBooleanArrayTest {

	@Test
	public void testStaticBooleanArray() {
		StaticBooleanArray sa = new StaticBooleanArray(123);
		assertEquals(123, sa.getSize());
	}

	@Test
	public void testSetAllValues() {
		StaticBooleanArray sa = new StaticBooleanArray(123);
		sa.setAllValues(true);
		for (int i=0; i<123; i++)
			assertEquals(true, sa.getValue(i));
		sa.setAllValues(false);
		for (int i=0; i<123; i++)
			assertEquals(false, sa.getValue(i));
	}

	@Test
	public void testGetSize() {
		StaticBooleanArray sa = new StaticBooleanArray(123);
		assertEquals(123, sa.getSize());
	}

	@Test
	public void testGetValueList() {
		StaticBooleanArray sa = new StaticBooleanArray(123);
		sa.setAllValues(true);
		boolean[] vList = sa.getValueList();
		for (int i=0; i<123; i++)
			assertEquals(true, vList[i]);
	}

	@Test
	public void testSetGetValue() {
		StaticBooleanArray sa = new StaticBooleanArray(123);
		
		sa.setAllValues(false);
		
		// set test values
		sa.setValue(0, true);
		sa.setValue(50, true);
		sa.setValue(122, true);
		
		assertEquals(true, sa.getValue(0));
		assertEquals(true, sa.getValue(50));
		assertEquals(true, sa.getValue(122));
	
	}


	@Test
	public void testCopyDeep() {
		StaticBooleanArray sa1 = new StaticBooleanArray(123);
		StaticBooleanArray sa2 = new StaticBooleanArray(123);
		
		sa1.setAllValues(false);
		sa2.setAllValues(false);
		
		// set test values
		sa1.setValue(0, true);
		sa1.setValue(50, true);
		sa1.setValue(122, true);

		// before deepCopy
		assertEquals(false, sa2.getValue(0));
		assertEquals(false, sa2.getValue(50));
		assertEquals(false, sa2.getValue(122));

		sa2.copyDeep(sa1);
		
		// after deepCopy
		assertEquals(true, sa2.getValue(0));
		assertEquals(true, sa2.getValue(50));
		assertEquals(true, sa2.getValue(122));
	
	}

}
