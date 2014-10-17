<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="GUILC001" description="This app provides OLED display driver interface for Segger GUI library.&#xA; OLED Display driver is interfaced with Segger GUI library using SPI001." descriptionURL="/doc/html/group___g_u_i_l_c001_app.html" mode="SHARABLE" URI="http://www.infineon.com/1.0.14/app/guilc001/0">
  <upWardMappingList xsi:type="ResourceModel:ProxyResource" href="../../GUISL001/1.0.22/guisl001_0.app#//@consumed.6"/>
  <provided xsi:type="ResourceModel:IntegerParameter" name="Mouse Support" evalFunction="&#xD;&#xA;        function ForwardMapping(){&#xD;&#xA;              var Res1 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;              var value1 = SCM.getIntValue(currentResource);&#xD;&#xA;              SCM.setIntValue(Res1,value1);&#xD;&#xA;            }&#xD;&#xA;            function BackwardMapping(){&#xD;&#xA;               var Res1 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;               var value1 = SCM.getIntValue(Res1);&#xD;&#xA;                SCM.setIntValue(currentResource,value1);&#xD;&#xA;             }&#xD;&#xA;            " URI="http://www.infineon.com/1.0.14/app/guilc001/0/guilc001_erwcmousesupport" downWardmappedList="//@consumed.2" maxValue="1" minValue="0">
    <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <upWardMappingList xsi:type="ResourceModel:ProxyResource" href="../../GUISL001/1.0.22/guisl001_0.app#//@consumed.12"/>
    <localValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <toolTipHelpDescription>Mouse support available</toolTipHelpDescription>
  </provided>
  <provided xsi:type="ResourceModel:EnumerationParameter" name="Read Display Configuration" URI="http://www.infineon.com/1.0.14/app/guilc001/0/guilc001_erwreaddisplayoption" multipleSelections="true">
    <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <localValue xsi:type="ResourceModel:StringValue" value="0"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="0"/>
    <toolTipHelpDescription>This option is valid only if mouse support is present.
 It enables the optional read support in display controller.
  It is used for reading from OLED or display controller.
When read support is not present, cache mode will be used and cache size must be set to 0xD500</toolTipHelpDescription>
    <item name="Enable Read Support" evalFunction="" URI="http://www.infineon.com/1.0.14/app/guilc001/0/guilc001_erwreaddisplayoption/0" maxValue="1" minValue="0">
      <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
      <localValue xsi:type="ResourceModel:StringValue" value="0"/>
      <globalValue xsi:type="ResourceModel:StringValue" value="0"/>
      <toolTipHelpDescription>This option is valid only if mouse support is present.
 It enables the optional read support in display controller.
  It is used for reading from OLED or display controller.
When read support is not present, cache mode will be used and cache size must be set to 0xD500</toolTipHelpDescription>
    </item>
  </provided>
  <provided xsi:type="ResourceModel:IntegerParameter" name="Set Cache Size" evalFunction="        &#xD;&#xA;        function ForwardMapping(){&#xD;&#xA;             var XMC1xxx=SCM.getSoftwareId().substring(0,1).compareTo(&quot;1&quot;);  &#xD;&#xA;             var value = SCM.getIntValue(currentResource);&#xD;&#xA;             var tempRes = SCM.getResource(&quot;guilc001_temperwcachesize&quot;);&#xD;&#xA;             if(value==0){&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;if(XMC1xxx==0){&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;&#x9;value = 4096;&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;} else {&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;&#x9;value = 32768;&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;}&#xD;&#xA;&#x9;&#x9;&#x9;  } &#xD;&#xA;              SCM.setIntValue(tempRes,value);&#xD;&#xA;&#x9;&#x9;&#x9;  &#xD;&#xA;         }        &#xD;&#xA;        function BackwardMapping(){&#xD;&#xA; &#x9;&#x9;&#x9;var tempRes = SCM.getResource(&quot;guilc001_temperwcachesize&quot;);&#xD;&#xA;            var value = SCM.getIntValue(tempRes);&#xD;&#xA;            var XMC1xxx=SCM.getSoftwareId().substring(0,1).compareTo(&quot;1&quot;);           &#xD;&#xA;            SCM.setIntValue(currentResource,value);&#xD;&#xA;            if(XMC1xxx==0){&#xD;&#xA;               var res_max= 10240;&#xD;&#xA;&#x9;&#x9;&#x9;   var res_min= 4096;&#x9;&#xD;&#xA;               SCM.setMinMaxValue(currentResource,res_min,res_max,1);&#xD;&#xA;            }    &#xD;&#xA;        }      &#xD;&#xA;        " URI="http://www.infineon.com/1.0.14/app/guilc001/0/guilc001_erwcachesize" downWardmappedList="//@consumed.3" maxValue="D500" minValue="1000">
    <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <localValue xsi:type="ResourceModel:StringValue" value="0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="8000"/>
    <toolTipHelpDescription>This sets the cache size to be used by GUI library. 
 It should be in the range of 4096 - 55K bytes(For XMC4000 Devices). 
When no read support is present, then cache mode is used. 
For mouse support, cache size needs to be set to 0xD500.</toolTipHelpDescription>
  </provided>
  <provided xsi:type="ResourceModel:API" description="The function configures the SPI bus at the run-time." URI="http://www.infineon.com/1.0.14/app/guilc001/0/lcd_x_serial_init" APIName="LCD_X_Serial_Init">
    <localValue xsi:type="ResourceModel:StringValue" value="-1"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="-1"/>
  </provided>
  <provided xsi:type="ResourceModel:API" description="This routine writes to display controller using SPI bus, with A0 = 0" URI="http://www.infineon.com/1.0.14/app/guilc001/0/lcd_x_serial_8_write00" APIName="LCD_X_Serial_8_Write00">
    <localValue xsi:type="ResourceModel:StringValue" value="-1"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="-1"/>
  </provided>
  <provided xsi:type="ResourceModel:API" description="This routine Writes to display controller using SPI bus, with A0 = 1" URI="http://www.infineon.com/1.0.14/app/guilc001/0/lcd_x_serial_8_write01" APIName="LCD_X_Serial_8_Write01">
    <localValue xsi:type="ResourceModel:StringValue" value="-1"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="-1"/>
  </provided>
  <provided xsi:type="ResourceModel:API" description="This is an event handler for the USB_DeviceAttached event." URI="http://www.infineon.com/1.0.14/app/guilc001/0/lcd_x_serial_m8_write01" APIName="LCD_X_Serial_M8_Write01">
    <localValue xsi:type="ResourceModel:StringValue" value="-1"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="-1"/>
  </provided>
  <provided xsi:type="ResourceModel:API" description="This routine reads from display controller using SPI bus, with A0 = 1" URI="http://www.infineon.com/1.0.14/app/guilc001/0/lcd_x_serial_m8_read01" APIName="LCD_X_Serial_M8_Read01">
    <localValue xsi:type="ResourceModel:StringValue" value="-1"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="-1"/>
  </provided>
  <provided xsi:type="ResourceModel:IntegerParameter" name="Dummy Variable" description="Dummy variable" evalFunction="&#xD;&#xA;        function ForwardMapping()&#xD;&#xA;        {       &#xD;&#xA;          var Res1 = SCM.getResource(&quot;spi/spi001_erwmode&quot;);&#xD;&#xA;          SCM.setIntValue(Res1,0);&#xD;&#xA;          var Res2 = SCM.getResource(&quot;spi/spi001_erwHBMode&quot;);&#xD;&#xA;          SCM.setIntValue(Res2,1);&#xD;&#xA;          var Res3 = SCM.getResource(&quot;spi/spi001_erwClockPolarity&quot;);&#xD;&#xA;          SCM.setIntValue(Res3,1);&#xD;&#xA;          var Res4 = SCM.getResource(&quot;spi/spi001_irwbaudrate&quot;);&#xD;&#xA;          SCM.setIntValue(Res4,10000000);&#xD;&#xA;          var Res5 = SCM.getResource(&quot;spi/spi001_irwSlaveSelect&quot;);&#xD;&#xA;          SCM.setIntValue(Res5,1);&#xD;&#xA;          var Res6 = SCM.getResource(&quot;spi/spi001_irwtxfifotrigger&quot;);&#xD;&#xA;          SCM.setIntValue(Res6,1);&#xD;&#xA;          var Res7 = SCM.getResource(&quot;spi/spi001_irwrxfifotrigger&quot;);&#xD;&#xA;          SCM.setIntValue(Res7,1);&#xD;&#xA;          var Res8 = SCM.getResource(&quot;io004/IO004_erwOutputMode/0&quot;);&#xD;&#xA;          SCM.setIntValue(Res8,1);  &#xD;&#xA;        }&#xD;&#xA;        " URI="http://www.infineon.com/1.0.14/app/guilc001/0/guilc001_irwdummy" downWardmappedList="//@consumed.4 //@consumed.5 //@consumed.6 //@consumed.7 //@consumed.8 //@consumed.9 //@consumed.10 //@consumed.11" maxValue="1" minValue="0">
    <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <localValue xsi:type="ResourceModel:StringValue" value="0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="989680"/>
    <toolTipHelpDescription></toolTipHelpDescription>
  </provided>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/spi">
    <downWardmappedList xsi:type="ResourceModel:App" href="../../SPI001/1.0.24/spi001_0.app#/"/>
    <requiredResource uriString="app/spi001/*" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/io004">
    <downWardmappedList xsi:type="ResourceModel:App" href="../../IO004/1.0.22/io004_0.app#/"/>
    <requiredResource uriString="app/io004/*" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/index1" upWardMappingList="//@provided.0" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <requiredResource uriString="" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/guilc001_temperwcachesize" upWardMappingList="//@provided.2" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="8000"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="8000"/>
    <requiredResource uriString="" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/spi/spi001_erwmode" upWardMappingList="//@provided.8" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <downWardmappedList xsi:type="ResourceModel:EnumerationParameter" href="../../SPI001/1.0.24/spi001_0.app#//@provided.44"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/spi/spi001_erwhbmode" upWardMappingList="//@provided.8" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <downWardmappedList xsi:type="ResourceModel:EnumerationParameter" href="../../SPI001/1.0.24/spi001_0.app#//@provided.55"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="1"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/spi/spi001_erwclockpolarity" upWardMappingList="//@provided.8" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <downWardmappedList xsi:type="ResourceModel:EnumerationParameter" href="../../SPI001/1.0.24/spi001_0.app#//@provided.63"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="1"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/spi/spi001_irwbaudrate" upWardMappingList="//@provided.8" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="989680"/>
    <downWardmappedList xsi:type="ResourceModel:IntegerParameter" href="../../SPI001/1.0.24/spi001_0.app#//@provided.48"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="989680"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/spi/spi001_irwslaveselect" upWardMappingList="//@provided.8" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <downWardmappedList xsi:type="ResourceModel:IntegerParameter" href="../../SPI001/1.0.24/spi001_0.app#//@provided.65"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="1"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/spi/spi001_irwtxfifotrigger" upWardMappingList="//@provided.8" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <downWardmappedList xsi:type="ResourceModel:IntegerParameter" href="../../SPI001/1.0.24/spi001_0.app#//@provided.58"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="1"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/spi/spi001_irwrxfifotrigger" upWardMappingList="//@provided.8" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <downWardmappedList xsi:type="ResourceModel:IntegerParameter" href="../../SPI001/1.0.24/spi001_0.app#//@provided.59"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="1"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.14/app/guilc001/0/io004/io004_erwoutputmode/0" upWardMappingList="//@provided.8" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <downWardmappedList xsi:type="ResourceModel:EnumItem" href="../../IO004/1.0.22/io004_0.app#//@provided.2/@item.0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="1"/>
  </consumed>
  <propertyConstants name="uridevice" value="device/xmc4500/"/>
  <categoryDescription description="Middleware Apps" name="Middleware Apps">
    <subCategory description="Graphic" name="Graphic"/>
  </categoryDescription>
  <manifestInfo version="1.0.14">
    <keywords>LCD</keywords>
    <keywords>Driver</keywords>
    <keywords>OLED</keywords>
    <keywords>SPI-4</keywords>
    <keywords>GUILC001</keywords>
    <keywords>Display</keywords>
    <properties xsi:type="ResourceModel:AppProperties_1_0" initProvider="true" singleton="true"/>
  </manifestInfo>
  <datagenerate fileName="GUILC001.c" templateFileName="GUILC001c.jet"/>
  <datagenerate fileName="GUILC001.h" fileType="HFILE" templateFileName="GUILC001.hdt" templateEngine="NONE" fileAction="COPY"/>
  <datagenerate fileName="LCDConf.c" templateFileName="LCDConf.cdt" templateEngine="NONE" fileAction="COPY"/>
  <datagenerate fileName="LCDConf.h" fileType="HFILE" templateFileName="LCDConf.hdt" templateEngine="NONE" fileAction="COPY"/>
  <datagenerate fileName="GUILC001_Conf.h" fileType="HFILE" templateFileName="GUILC001_Confh.jet"/>
  <datagenerate fileName="GUILC001_Conf.c" templateFileName="GUILC001_Confc.jet"/>
  <datagenerate fileName="Dave/Generated/inc/GUILC001" fileType="HFILE" templateFileName="Dave/Generated/inc/GUILC001" templateEngine="NONE" fileAction="INCLUDE"/>
  <softwareIdList>45.0.1</softwareIdList>
  <softwareIdList>45.0.2</softwareIdList>
  <softwareIdList>45.0.3</softwareIdList>
  <softwareIdList>45.2.3</softwareIdList>
  <softwareIdList>45.4.2</softwareIdList>
  <softwareIdList>45.4.3</softwareIdList>
  <softwareIdList>45.0200.1</softwareIdList>
  <softwareIdList>45.0200.2</softwareIdList>
  <softwareIdList>45.0200.3</softwareIdList>
  <softwareIdList>45.0202.3</softwareIdList>
  <softwareIdList>45.0204.3</softwareIdList>
  <softwareIdList>45.0204.2</softwareIdList>
  <softwareIdList>44.0.3</softwareIdList>
  <softwareIdList>44.00.5</softwareIdList>
  <softwareIdList>44.02.3</softwareIdList>
  <softwareIdList>44.02.5</softwareIdList>
  <softwareIdList>12.0100.7</softwareIdList>
  <softwareIdList>13.0102.7</softwareIdList>
  <softwareIdList>11.0100.7</softwareIdList>
  <softwareIdList>11.0100.9</softwareIdList>
  <softwareIdList>12.0101.7</softwareIdList>
  <softwareIdList>44.0200.5</softwareIdList>
  <softwareIdList>44.0202.3</softwareIdList>
  <softwareIdList>44.0202.5</softwareIdList>
  <softwareIdList>44.0200.3</softwareIdList>
  <softwareIdList>45.0300.1</softwareIdList>
  <softwareIdList>45.0300.3</softwareIdList>
  <softwareIdList>45.0302.3</softwareIdList>
  <softwareIdList>45.0304.2</softwareIdList>
  <softwareIdList>45.0300.2</softwareIdList>
  <softwareIdList>45.0304.3</softwareIdList>
  <softwareIdList>11.0100.10</softwareIdList>
  <softwareIdList>11.0100.11</softwareIdList>
  <softwareIdList>12.0101.11</softwareIdList>
  <softwareIdList>12.0102.10</softwareIdList>
  <softwareIdList>12.0102.11</softwareIdList>
  <softwareIdList>13.0101.10</softwareIdList>
  <softwareIdList>13.0101.11</softwareIdList>
  <softwareIdList>13.0102.10</softwareIdList>
  <softwareIdList>13.0102.11</softwareIdList>
  <softwareIdList>13.0102.9</softwareIdList>
</ResourceModel:App>
