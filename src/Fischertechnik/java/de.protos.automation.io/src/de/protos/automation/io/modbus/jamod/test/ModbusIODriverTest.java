package de.protos.automation.io.modbus.jamod.test;


/**
 * @author Thomas Schuetz
 * ModbusIODriverTest can only be executed with very specific attached Modbus Hardware
 */
public class ModbusIODriverTest {
/*
	@BeforeClass public static void setUp() {
		try {
			driver = new ModbusIODriver(InetAddress.getByName("192.168.1.140"), 502, 32, 32);
			driver.connect();
		} catch (UnknownHostException e) {
			fail("ModbusIODriver could not be instantiated or connected");
			e.printStackTrace();
		}
	}

	@AfterClass public static void tearDown() {
		driver.disconnect();
	}
	
	@Test
	public void testSet32Outputs() {
		// set all Outputs on
		for (int channel = 0; channel<32; channel++)
			driver.setStatus(channel, true);
		waitForHardware(100);
		// set all Outputs off
		for (int channel = 0; channel<32; channel++)
			driver.setStatus(channel, false);
		waitForHardware(1000);
	}


	@Test
	public void testGet32Inputs() {
		for (int channel = 0; channel<8; channel++){
			boolean result = driver.getStatus(channel);
			assertEquals( "getStatus should always be false here", false, result);  
		}
	}
	
	@Test
	public void testIOLoop() {
		// this test assumes following hardware connections:
		// output 31 -> input 0
		// output 7 -> input 31
		
		// check start condition of inputs
		assertEquals("output 31 -> input 0", false, driver.getStatus(0));
		//assertEquals("output 7 -> input 31", false, driver.getStatus(31));

		// set outputs
		driver.setStatus(31, true);
		driver.setStatus(7, true);
		
		waitForHardware(1000);
		
		// check new condition
		assertEquals("output 31 -> input 0", true, driver.getStatus(0));
		//assertEquals("output 7 -> input 31", true, driver.getStatus(31));
		
		// reset outputs
		driver.setStatus(31, false);
		driver.setStatus(7, false);
		
		waitForHardware(1000);
		
		
	}
	
	@Test
	public void testFastIOLoop() {
		for (int i=0; i<100; i++){
			boolean current_status = driver.getStatus(0);
			driver.setStatus(31, !current_status);
			while(true){
				waitForHardware(1);
				if(driver.getStatus(0) == !current_status) 
					break;
			}
			current_status = !current_status;
		}
		driver.setStatus(31, false);
	}

	
	@Test
	public void testCoil() {
		// TODOTS: noch nicht fertig
		
		byte bcoil;
		int coil, offset, bit;

		bcoil = 0;
		offset = bcoil % (byte)8;
		bit = bcoil - offset * 8;
		assertEquals(0, offset);
		assertEquals(0, bit);
		
		coil = 8;
		offset = coil % 8;
		bit = coil - offset * 8;
		assertEquals(1, offset);
		assertEquals(0, bit);

		coil = 15;
		offset = coil % 8;
		bit = coil - offset * 8;
		assertEquals(1, offset);
		assertEquals(7, bit);
	}
	
	
	// Helpers
	private void waitForHardware(int ms_time) {
		// This function waits ms_time milliseconds to be sure to avoid side effects on the other tests
		try {
			Thread.sleep(ms_time);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private static ModbusIODriver driver;
*/
}
