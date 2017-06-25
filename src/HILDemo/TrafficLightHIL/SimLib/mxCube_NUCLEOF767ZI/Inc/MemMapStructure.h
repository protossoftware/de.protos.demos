//*****************************************************************************
// HILTI Entwicklungsgesellschaft mbH
// Hiltistr. 6 , D-86916 Kaufering (Germany)
// (c) Copyright by Hilti, ALL RIGHTS RESERVED
//*****************************************************************************
/// @file         MemMapStructure.h
/// @brief        structure of memory map
///
/// @code
/// SVN-Information:
/// \$Date: 2017-04-13 08:38:35 +0200 (Do, 13. Apr 2017) $
/// \$Author: jungthom $
/// \$URL: svn://kfg-hegjdp01/jd_test/SW-Testing/Hilti_SW-SimulationPlatform/SimLib/mxCube_NUCLEOF767ZI/Inc/MemMapStructure.h $
/// \$Revision: 2323 $
/// @endcode
//*****************************************************************************

#ifndef MEMMAPSTRUCTURE_H
#define MEMMAPSTRUCTURE_H

#include <stdint.h>
//------------------------------------------------------------------------------
/// definition of memory map inside CMS
//------------------------------------------------------------------------------
typedef struct tMEMMAPSTRUCTURE          /// Struktur für Inhalte der MemoryMap
{
  //0x00-0x01
  uint8_t ubTPS_active_byte           :8;
  uint8_t bMflag                      :1;  // memory flag for aborted cycles, see spezification of the charger. In MMap always zero
  uint8_t bChargeActivityFlag         :1;  // TRUE = chargingprocess active; FALSE = Battery Temperature is out of range  0°C >T >60°C or out of voltage range
  uint8_t bCflag                      :1;  // TRUE = during the charging process
  uint8_t bSOC25Flag                  :1;  // State of charge >= 25%
  uint8_t bSOC50Flag                  :1;  // State of charge >= 50%
  uint8_t bSOC75Flag                  :1;  // State of charge >= 75%
  uint8_t bSOC100Flag                 :1;  // State of charge >= 100%
  uint8_t bStartOCV                   :1;  // TRUE = OCV-Measurement Anforderung vom Lader

  //0x02-0x0D
  uint8_t ubBattSec[12];                   // TPS BattSec. No.

  //0x0E-0x13
  uint8_t ubBattSN[4];                     // Batt serial No.
  uint8_t                             :8;
  uint8_t                             :8;

  //0x14-0x15
  uint8_t ubCellmanufacturer          :4;
  uint8_t ubCellsS                    :4;
  uint8_t ubCellsP                    :3;
  uint8_t ubCapacityCell              :5;

  //0x16-0x17
  uint8_t ubVcharge_cell              :8;
  uint8_t ubVmin_cell                 :8;

  //0x18-0x19
  uint8_t ubVmax_CMS                  :8;
  uint8_t ubNTC_DownDelay             :7;
  uint8_t                             :1;

  //0x1A-0x1B
  uint8_t ubVmin_CMS                  :8;
  uint8_t ubIcharge1_cell             :7;
  uint8_t                             :1;

  //0x1C-0x1D
  uint8_t ubIcharge2_cell             :7;
  uint8_t                             :1;
  uint8_t ubIcharge3_cell             :7;
  uint8_t                             :1;

  //0x1E-0x1F
  uint8_t ubVmin_disc                 :7;
  uint8_t                             :1;
  uint8_t ubSelfHoldTime              :8;

  //0x20-0x21
  uint8_t ubU25_cell                  :6;
  uint8_t                             :2;
  uint8_t ubU50_cell                  :6;
  uint8_t                             :2;

  //0x22-0x23
  uint8_t ubI75_1_cell                :6;
  uint8_t                             :2;
  uint8_t ubI75_2_cell                :6;
  uint8_t                             :2;

  //0x24-0x25
  uint8_t ubI100_1_SOC                :8;
  uint8_t ubI100_2_SOC                :8;

  //0x26-0x27
  uint8_t ubIend_cell                 :6;
  uint8_t                             :2;
  uint8_t ubTend                      :8;

  //0x28-0x29
  uint8_t ubTimeRecharge              :5;
  uint8_t                             :3;
  uint8_t ubRechargeCounter           :7;
  uint8_t                             :1;

  //0x2A-0x2B
  uint8_t ubTminNormalCharge          :5;
  uint8_t                             :3;
  uint8_t ubTmaxNormalCharge          :5;
  uint8_t ubExtendedTechnology        :3;

  //0x2C-0x2D
  uint8_t ubTmaxDisc                  :6;
  uint8_t                             :2;
  uint8_t ubT_I23                     :7;
  uint8_t                             :1;

  //0x2E-0x2F
  uint8_t ubTechnology                :3;
  uint16_t                             :11;
  uint8_t bActiveCoolingBit           :1;
  uint8_t                             :1;

  //0x30-0x31
  uint8_t ubSoc10Value                :7;  // SOC 10% -> uwSOC10
  uint8_t                             :1;
  uint8_t ubSoc25Value                :7;  // SOC 25% -> uwSOC25
  uint8_t                             :1;

  //0x32-0x33
  uint8_t ubSoc50Value                :7;  // SOC 50% -> uwSOC50
  uint8_t                             :1;
  uint8_t ubSoc75Value                :7;  // SOC 75% -> uwSOC75
  uint8_t                             :1;

  //0x34-0x35
  uint8_t ubI_Disc500                 :8;
  uint8_t ubToolClass                 :8;

  //0x36-0x37
  uint16_t uwChecksumRO                :16; // Checksumme über vorstehenden Bereich

  //0x38-0x39
  uint16_t uwCcycles                   :10;
  uint8_t                             :6;

  //0x3A-0x3B
  uint16_t uwAcycles                   :10;
  uint8_t                             :6;

  //0x3C-0x3D
  uint16_t uwRcycles                   :10;
  uint8_t                             :6;

  //0x3E-0x3F
  uint16_t uwFcounter25_50             :9;
  uint8_t ubNTCdownCellVoltageCharge  :7;

  //0x40-0x41
  uint16_t uwFcounter50_75             :9;
  uint8_t ubNTCdownTemperatureCharge  :7;

  //0x42-0x43
  uint16_t uwFcounter75_100            :9;
  uint8_t ubMMapVersion               :7;

  //0x44-0x45
  uint16_t uwChargerModel1             :10;
  uint8_t                             :6;

  //0x46-0x47
  uint16_t uwChargerModel2             :10;
  uint8_t                             :6;

  //0x48-0x49
  uint16_t uwChargerModel3             :10;
  uint8_t                             :6;

  //0x4A-0x4B
  uint16_t uwChargerModel4             :10;
  uint8_t                             :6;

  //0x4C-0x4D
  uint16_t uwChargerModel5             :10;
  uint8_t                             :6;

  //0x4E-0x4F
  uint16_t uwChargerModel6             :10;
  uint8_t                             :6;

  //0x50-0x51
  uint16_t uwNTCdownCounterVminCMS     :10; // NTCdownCounter wegen uwVminCMS
  uint8_t                             :3;
  uint8_t bNTCTestCycle               :1;
  uint8_t bNTCdownSet                 :1;
  uint8_t bNTCdownAcknowledge         :1;
                                            
  //0x52-0x53                               
  uint16_t uwNTCdownCounterVminDisc    :10; // NTCdownCounter wegen uwVminDisc
  uint8_t                             :6;
                                            
  //0x54-0x55                               
  uint16_t uwNTCdownCounterTmaxDisc    :10; // NTCdownCounter wegen ubTmaxDisc
  uint8_t                             :6;

  //0x56-0x57
  uint8_t ubDefWireToSingleCell       :8;
  uint8_t bChargeModeActive           :1;
  uint8_t bLowvoltagebit              :1;
  uint8_t                             :6;

  //0x58-0x59
  uint8_t ubU_LowVoltage              :8;
  uint8_t ubTime_LowVoltage           :8;

  //0x5A-0x5B
  uint8_t ubAkkuTypeNumber            :8;
  uint8_t                             :8;

  //0x5C-0x5D
  uint8_t ubCMSIdentifier1ByteL       :8;
  uint8_t ubCMSIdentifier1ByteH       :8;

  //0x5E-0x5F
  uint8_t ubCMSIdentifier2ByteL       :8;
  uint8_t ubCMSIdentifier2ByteH       :8;

  //0x60-0x61
  uint8_t ubOverloadSignalTime        :8;  // Zeit der Überlastanzeige der LEDs (durch K2 signalisiert)
  uint8_t ubSOC_DelayTime             :8;  // Wartezeit in der keine SOC-Anzeige während der Tool Selbsthaltung mögl. ist

  //0x62-0x63
  uint8_t ubWireDefectCounter         :8;  // Zähler für festgestellte Drahtbrüche
  uint8_t ubWireDefectLimit           :8;  // Limit ab dem NTC_Down dauerhaft gesetzt bleibt bei Def.-Wire, wenn erneut ein Drahtbruch festgestellt wird

  //0x64-0x65
  uint8_t ubIcharge0_cell             :7;
  uint8_t                             :1;
  uint8_t ubVcharge0_cell             :8;

  //0x66-0x67
  uint8_t ubTminColdCharge            :8;
  uint8_t ubTcyclesLow                :8;

  //0x68-0x69
  uint8_t ubTcyclesHigh               :8;
  uint8_t                             :8;

  //0x6A-0x6B
  uint8_t                             :8;
  uint8_t                             :8;

  //0x6C-0x6D
  uint8_t                             :8;
  uint8_t ubCap_act                   :8;

  //0x6E-0x6F
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x70 - 0x71
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x72 - 0x73
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x74 - 0x75
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x76 - 0x77
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x78 - 0x79
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x7A - 0x7B
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x7C - 0x7D
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x7E - 0x7F
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x80 - 0x81
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x82 - 0x83
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x84 - 0x85
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x86 - 0x87
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x88 - 0x89
  uint8_t                             :8;
  uint8_t                             :8;
  
  //0x8A - 0x8B
  uint8_t                             :8;
  uint8_t                             :8;

  //0x8C-0x8D
  uint8_t ubRi_DC_Cell                :8;  // Wert des Innenwiderstandes einer Zelle (wird bei K1 ans Tool übertragen)
  uint8_t ubReserved1_K1              :8;  // zufünftiges Datum1, das bei K1 an das Tool übertragen wird

  //0x8E-0x8F
  uint8_t ubReserved2_K1              :8;  // zufünftiges Datum2, das bei K1 an das Tool übertragen wird
  uint8_t ubFuseVoltage               :8;  // Output voltage for fuse activation

  //0x90-0x91
  uint8_t ubFuseActivationTemperature :8;  // Temperature limit for fuse activation
  uint8_t ubFuseActivationCellVoltage :8;  // Single-Cell-Volttage limit for fuse activation

  //0x92-0x93
  uint8_t ubFuseActivationDelayTime   :8;  // Delay for fuse activation
  uint8_t ubCellDebalanceMax          :8;  // Maximal erlaubte Zelldebalanzierung [0.01 V]

  //0x94-0x95
  uint8_t                             :8;
  uint8_t                             :8;

  uint16_t uwMagicWord                :16;  // 0x0096
  uint8_t                             :8;  // 0x0098
  uint8_t                             :8;  // 0x0099
  uint8_t                             :8;  // 0x009A
  uint8_t                             :8;  // 0x009B
  uint8_t                             :8;  // 0x009C
  uint8_t                             :8;  // 0x009D
  uint8_t                             :8;  // 0x009E
  uint8_t                             :8;  // 0x009F
  uint8_t                             :8;  // 0x00A0
  uint8_t                             :8;  // 0x00A1
  uint8_t                             :8;  // 0x00A2
  uint8_t                             :8;  // 0x00A3
  uint8_t                             :8;  // 0x00A4
  uint8_t                             :8;  // 0x00A5
  uint8_t                             :8;  // 0x00A6
  uint8_t                             :8;  // 0x00A7
  uint8_t                             :8;  // 0x00A8
  uint8_t                             :8;  // 0x00A9
  uint8_t                             :8;  // 0x00AA
  uint8_t                             :8;  // 0x00AB
  uint8_t                             :8;  // 0x00AC
  uint8_t                             :8;  // 0x00AD
  uint8_t                             :8;  // 0x00AE
  uint8_t                             :8;  // 0x00AF
  uint8_t                             :8;  // 0x00B0
  uint8_t                             :8;  // 0x00B1
  uint8_t                             :8;  // 0x00B2
  uint8_t                             :8;  // 0x00B3
  uint8_t                             :8;  // 0x00B4
  uint8_t                             :8;  // 0x00B5
  uint8_t                             :8;  // 0x00B6
  uint8_t                             :8;  // 0x00B7
  uint8_t                             :8;  // 0x00B8
  uint8_t                             :8;  // 0x00B9
  uint8_t                             :8;  // 0x00BA
  uint8_t                             :8;  // 0x00BB
  uint8_t                             :8;  // 0x00BC
  uint8_t                             :8;  // 0x00BD
  uint8_t                             :8;  // 0x00BE
  uint8_t                             :8;  // 0x00BF
  uint8_t                             :8;  // 0x00C0
  uint8_t                             :8;  // 0x00C1
  uint8_t                             :8;  // 0x00C2
  uint8_t                             :8;  // 0x00C3
  uint8_t                             :8;  // 0x00C4
  uint8_t                             :8;  // 0x00C5
  uint16_t uwCRCChecksumRO            :16;  // 0x00C6 Checksumme RO Bereiche
  uint8_t                             :8;  // 0x00C8
  uint8_t                             :8;  // 0x00C9
  uint8_t                             :8;  // 0x00CA
  uint8_t                             :8;  // 0x00CB
  uint8_t                             :8;  // 0x00CC
  uint8_t                             :8;  // 0x00CD
  uint8_t                             :8;  // 0x00CE
  uint8_t                             :8;  // 0x00CF
  uint8_t                             :8;  // 0x00D0
  uint8_t                             :8;  // 0x00D1
  uint8_t                             :8;  // 0x00D2
  uint8_t                             :8;  // 0x00D3
  uint8_t                             :8;  // 0x00D4
  uint8_t                             :8;  // 0x00D5
  uint8_t                             :8;  // 0x00D6
  uint8_t                             :8;  // 0x00D7
  uint8_t                             :8;  // 0x00D8
  uint8_t                             :8;  // 0x00D9
  uint8_t                             :8;  // 0x00DA
  uint8_t                             :8;  // 0x00DB
  uint8_t                             :8;  // 0x00DC
  uint8_t                             :8;  // 0x00DD
  uint8_t                             :8;  // 0x00DE
  uint8_t                             :8;  // 0x00DF
  uint8_t                             :8;  // 0x00E0
  uint8_t                             :8;  // 0x00E1
  uint8_t                             :8;  // 0x00E2
  uint8_t                             :8;  // 0x00E3
  uint8_t                             :8;  // 0x00E4
  uint8_t                             :8;  // 0x00E5
  uint8_t                             :8;  // 0x00E6
  uint8_t                             :8;  // 0x00E7
  uint8_t                             :8;  // 0x00E8
  uint8_t                             :8;  // 0x00E9
  uint8_t                             :8;  // 0x00EA
  uint8_t                             :8;  // 0x00EB
  uint8_t                             :8;  // 0x00EC
  uint8_t                             :8;  // 0x00ED
  uint8_t                             :8;  // 0x00EE
  uint8_t                             :8;  // 0x00EF
} tMEMMAPSTRUCTURE;


typedef struct tAKKU_RAMDATASTRUCT{
	uint16_t packVoltage;
	uint16_t cellVoltage[10];
	uint16_t ntcVoltage;
} tAKKU_RAMDATASTRUCT;

typedef struct tAKKU_LIVEDATASTRUCT{
	uint8_t sCellsK12;
	uint8_t pCellsK12;
	uint8_t errorCodeLow;
	uint8_t errorCodeHigh;
	uint8_t syncResult;
	uint8_t ntcDownTestResult;
	uint8_t packVoltageAtDiagTimeLow;
	uint8_t packVoltageAtDiagTimeHigh;
	int8_t 	temperatureAtDiagTime;
	uint8_t debalancingLimit;
	uint8_t fwVersionHigh;
	uint8_t fwVersionLow;
}tAKKU_LIVEDATASTRUCT;

typedef union tAKKU_RAMDATASTRUCT_UNION{
	uint8_t 			ubData[sizeof(tAKKU_RAMDATASTRUCT)];
	tAKKU_RAMDATASTRUCT sMM;
}tAKKU_RAMDATASTRUCT_UNION;

typedef union tMEMMAPSTRUCTURE_UNION                  /// Union für Inhalte der MemoryMap
{
  uint8_t           ubData[sizeof(tMEMMAPSTRUCTURE)]; ///< aktuelle Mem.-Map im Flash als Bytearray
  tMEMMAPSTRUCTURE  sMM;                              ///< aktuelle Mem.-Map im Flash als Struktur
} tMEMMAPSTRUCTURE_UNION;


#endif
