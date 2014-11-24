package de.protos.automation.io.modbus.jamod;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.HashMap;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;
import javax.swing.Timer;

public class ModbusGui extends JFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	// Modbus
	ModbusIODriver modbusDriver = null;
	private static final int inputRange = 32;
	private static final int outputRange = 32;

	Timer pollingTimer = null;

	JPanel panel = null;
	
	HashMap<JButton, Integer> outputButtons = new HashMap<JButton, Integer>(outputRange); 
	HashMap<Integer, JTextField> inputTexts = new HashMap<Integer, JTextField>(inputRange); 
	
	public ModbusGui() {

		panel = new JPanel();
		getContentPane().add(panel);

		panel.setLayout(null);

		// Modbus
		initModbus();
		initInputList();
		initOutputList();
		
		// settings for Main Window
		setTitle("Modbus GUI");
		setSize(600, 1000);
		setLocation(10, 10);
		// setLocationRelativeTo(null);
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		// Timer for polling Inputs
		pollingTimer = new Timer(500, this);
		pollingTimer.start();

	}

	private void initModbus() {

		// TODOTS: this has to be made much more efficient on a lower level
		try {
			modbusDriver = new ModbusIODriver(
					InetAddress.getByName("192.168.1.140"), 502, inputRange,
					outputRange);
			modbusDriver.connect();
			modbusDriver.readInputBufferFromHW();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				ModbusGui gui = new ModbusGui();
				gui.setVisible(true);
			}
		});
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		
		if (e.getSource().equals(pollingTimer)) {
			displayInputs();
		}
		else {
			Integer channel = outputButtons.get(e.getSource());
			if (channel==null){
				return;
			}
			else {
				toggleOutput((JButton)e.getSource(), channel);
			}
		}
	}

	// Handlers for specific Actions
	private void displayInputs() {
		modbusDriver.readInputBufferFromHW();

		for (int channel = 0; channel < inputRange; channel++) {
			if (modbusDriver.getInput(channel) == true) {
				inputTexts.get(channel).setBackground(Color.GREEN);
			} else {
				inputTexts.get(channel).setBackground(Color.LIGHT_GRAY);
			}
		}
	}

	private void toggleOutput(JButton button, int channel) {
		if (channel < 0 && channel >= outputRange){
			System.out.println("ERROR: channel: "+channel+" out of inputRange");
			return;
		}
		if (modbusDriver.getOutput(channel)) {
			modbusDriver.setOutput(channel, false);
			button.setBackground(Color.LIGHT_GRAY);
		} else {
			modbusDriver.setOutput(channel, true);
			button.setBackground(Color.GREEN);
		}
		modbusDriver.writeOutputBufferToHW();
	}

	private void initInputList(){

		final int inputOffset = 2; // offset for additional WAGO Module (750-610) -> 2 additional inputs
		
		addInputTextField(new String("--- not used ---"),0);
		addInputTextField(new String("--- not used ---"),1);

		addInputTextField(new String("SensorEinlegestation"),0+inputOffset);
		addInputTextField(new String("SensorBand1"),1+inputOffset);
		addInputTextField(new String("Schieber1Vorne"),2+inputOffset);
		addInputTextField(new String("Schieber1Hinten"),3+inputOffset);
		addInputTextField(new String("SensorBand2"),4+inputOffset);
		addInputTextField(new String("SensorBand3"),5+inputOffset);
		addInputTextField(new String("Schieber2Vorne"),6+inputOffset);
		addInputTextField(new String("Schieber2Hinten"),7+inputOffset);
		addInputTextField(new String("SensorBand4"),8+inputOffset);

		for (int i=inputTexts.size();i<inputRange; i++){
			addInputTextField(new String("--- not used ---"),i);
		}
		displayInputs();
	}
	
	private void addInputTextField(String text, int channel){
		int startX = 100;
		int startY = 100;
		int incY = 20;
		
		JTextField textField = new JTextField(""+channel+"   :   "+text);
		textField.setBounds(startX, startY+channel*incY, 200, 20);
		textField.setHorizontalAlignment(SwingConstants.LEFT);
		textField.setBackground(Color.LIGHT_GRAY);
		inputTexts.put(channel, textField);
		panel.add(textField);
		
	}
	
	private void initOutputList(){
		addOutputButton("Band1     L/R",0);
		addOutputButton("Band1     ON/OFF",1);
		addOutputButton("Schieber1 L/R",2);
		addOutputButton("Schieber1 ON/OFF",3);
		addOutputButton("Band2     L/R",4);
		addOutputButton("Band2     ON/OFF",5);
		addOutputButton("Fraese    L/R",6);
		addOutputButton("Fraese    ON/OFF",7);
		addOutputButton("Band3     L/R",8);
		addOutputButton("Band3     ON/OFF",9);
		addOutputButton("Bohrer    L/R",10);
		addOutputButton("Bohrer    ON/OFF",11);
		addOutputButton("Schieber2 L/R",12);
		addOutputButton("Schieber2 ON/OFF",13);
		addOutputButton("Band4     L/R",14);
		addOutputButton("Band4     ON/OFF",15);
		for (int i=outputButtons.size();i<outputRange; i++){
			addOutputButton("--- not used ---",i);
		}
	}
	
	private void addOutputButton(String text, int channel){
		int startX = 300;
		int startY = 100;
		int incY = 20;
		
		JButton button = new JButton(""+channel+"   :   "+text);
		button.setBounds(startX, startY+channel*incY, 200, 20);
		button.setHorizontalAlignment(SwingConstants.LEFT);
		button.setBackground(Color.LIGHT_GRAY);
		button.addActionListener(this);
		outputButtons.put(button,channel);
		panel.add(button);
	}
}



