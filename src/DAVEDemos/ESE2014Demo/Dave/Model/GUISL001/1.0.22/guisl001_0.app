<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="GUISL001" description="This is Segger Graphic library with graphical user &#xA;interface in Non-RTOS environment.It is designed to &#xA;provide an efficient, processor and display controller &#xA;independent graphical user interface for any application &#xA;that operates with a graphical display." descriptionURL="/doc/html/group___g_u_i_s_l001_app.html" mode="SHARABLE" URI="http://www.infineon.com/1.0.22/app/guisl001/0">
  <provided xsi:type="ResourceModel:StringParameter" name="Library" evalFunction="      &#xD;&#xA;        function ForwardMapping()&#xD;&#xA;         {&#xD;&#xA;           var Res0 = SCM.getResource(&quot;displaystring&quot;);&#xD;&#xA;           var value0 = SCM.getIntValue(currentResource);&#xD;&#xA;           var Res1 = SCM.getResource(&quot;displaystring1&quot;);&#xD;&#xA;           SCM.setIntValue(Res0,6);&#xD;&#xA;           SCM.setIntValue(Res1,0);&#xD;&#xA;         }&#xD;&#xA;         function BackwardMapping()&#xD;&#xA;         {&#xD;&#xA;           var Res0 = SCM.getResource(&quot;displaystring&quot;);&#xD;&#xA;           var value0 = SCM.getIntValue(Res0);&#xD;&#xA;           var Res1 = SCM.getResource(&quot;displaystring1&quot;);&#xD;&#xA;           var value1 = SCM.getIntValue(Res1);&#xD;&#xA;           if (value0 == 2)&#xD;&#xA;           { &#xD;&#xA;             SCM.setStringValue(currentResource, &quot;guisl001_WithoutMouse&quot;);&#xD;&#xA;           }&#xD;&#xA;           else if ((value0 == 1) || ((value0 == 1) &amp;&amp; (value1 == 2) ))&#xD;&#xA;           {&#xD;&#xA;             SCM.setStringValue(currentResource, &quot;guisl001&quot;);&#xD;&#xA;           }&#xD;&#xA;           else if (value1 == 2) &#xD;&#xA;           {&#xD;&#xA;             SCM.setStringValue(currentResource, &quot;guisl001_WithoutMouse&quot;);&#xD;&#xA;           }&#xD;&#xA;           else if (value0 == 3)&#xD;&#xA;           {&#xD;&#xA; &#x9;&#x9;&#x9;   var XMC1x =SCM.getSoftwareId().substring(0,1).compareTo(&quot;1&quot;);&#xD;&#xA;               if( XMC1x == 0 )&#xD;&#xA;&#x9;&#x9;&#x9;   {&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;&#x9;SCM.setStringValue(currentResource, &quot;guisl001_xmc1&quot;);&#xD;&#xA;               }&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;else{&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;SCM.setStringValue(currentResource, &quot;guisl001_WithoutMouse_WithoutWin&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;}&#xD;&#xA;           }&#xD;&#xA;           else if (((value1 == 1) &amp;&amp; (value0 == 4)) || ((value1 == 3) &amp;&amp; (value0 == 4)))&#xD;&#xA;           {&#xD;&#xA; &#x9;&#x9;&#x9;   var XMC1x =SCM.getSoftwareId().substring(0,1).compareTo(&quot;1&quot;);&#xD;&#xA;               if( XMC1x == 0 )&#xD;&#xA;&#x9;&#x9;&#x9;   {&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;&#x9;SCM.setStringValue(currentResource, &quot;guisl001_xmc1&quot;);&#xD;&#xA;               }&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;else{&#xD;&#xA;&#x9;              SCM.setStringValue(currentResource, &quot;guisl001_WithoutMouse&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;}&#xD;&#xA;           }&#xD;&#xA;           else if (value1 == 3)&#xD;&#xA;           {&#xD;&#xA; &#x9;&#x9;&#x9;   var XMC1x =SCM.getSoftwareId().substring(0,1).compareTo(&quot;1&quot;);&#xD;&#xA;               if( XMC1x == 0 )&#xD;&#xA;&#x9;&#x9;&#x9;   {&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;&#x9;SCM.setStringValue(currentResource, &quot;guisl001_xmc1&quot;);&#xD;&#xA;               }&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;else{&#xD;&#xA;              SCM.setStringValue(currentResource, &quot;guisl001_WithoutMouse&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;  }&#xD;&#xA;           }&#xD;&#xA;           else&#xD;&#xA;           { &#xD;&#xA; &#x9;&#x9;&#x9;   var XMC1x =SCM.getSoftwareId().substring(0,1).compareTo(&quot;1&quot;);&#xD;&#xA;               if( XMC1x == 0 )&#xD;&#xA;&#x9;&#x9;&#x9;   {&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;&#x9;SCM.setStringValue(currentResource, &quot;guisl001_xmc1&quot;);&#xD;&#xA;               }&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;else{&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;SCM.setStringValue(currentResource, &quot;guisl001_WithoutMouse_WithoutWin&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;}&#xD;&#xA;           }&#xD;&#xA;        }&#xD;&#xA;        " URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_library_note" downWardmappedList="//@consumed.4 //@consumed.5">
    <defaultValue xsi:type="ResourceModel:StringValue" value="No library available"/>
    <localValue xsi:type="ResourceModel:StringValue" value="No library available"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="guisl001_WithoutMouse_WithoutWin"/>
    <toolTipHelpDescription>The SEGGER library  has to be listed above the math library(m) in project settings.
Press: >Project >Active Projects Properties >C/C++Build >Settings >ARM GCC Linker >Libraries.
Use the arrow to  move the SEGGER library above math library (m) 
For further details please refer to the help document:
 >Help >Help Content >DAVE Apps >GUISL001 >App Configuration Documentation</toolTipHelpDescription>
  </provided>
  <provided xsi:type="ResourceModel:EnumerationParameter" name="USB Devices" evalFunction="&#xD;&#xA;           function ForwardMapping()&#xD;&#xA;           {       &#xD;&#xA;               var Res0 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;               var value0 = SCM.getIntValue(currentResource);&#xD;&#xA;               SCM.setIntValue(Res0,value0);&#xD;&#xA;               var Res1 = SCM.getResource(&quot;lcdapp/guilc001_erwcmousesupport&quot;); &#xD;&#xA;               var Res2 = SCM.getResource(&quot;usbldapp/usbld001_irwrtos_mode&quot;);&#xD;&#xA;           }&#xD;&#xA;           function BackwardMapping()&#xD;&#xA;           {   &#xD;&#xA;              var Res0 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;              var value0 = SCM.getIntValue(Res0);&#xD;&#xA;              SCM.setIntValue(currentResource,value0);   &#xD;&#xA;           }&#xD;&#xA;         " URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_erwusbdevices" downWardmappedList="//@consumed.0">
    <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <localValue xsi:type="ResourceModel:StringValue" value="0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="2"/>
    <toolTipHelpDescription>This displays the USB devices available to the user.
 Either of Keyboard or Mouse can be used at a time.</toolTipHelpDescription>
    <item name="Use Mouse" evalFunction="&#xD;&#xA;            function ForwardMapping()&#xD;&#xA;            {       &#xD;&#xA;                var dep = &quot;DependentApp&quot;;&#xD;&#xA;                var appname = SCM.getResource(&quot;mouseapp&quot;); &#xD;&#xA;                SCM.setStringValue(appname,dep); &#xD;&#xA;                var appname1 = SCM.getResource(&quot;keyboardapp&quot;); &#xD;&#xA;                SCM.setStringValue(appname1,dep);   &#xD;&#xA;                var appname2 = SCM.getResource(&quot;usbldapp&quot;);&#xD;&#xA;                SCM.setStringValue(appname2,dep);  &#xD;&#xA;                var appname3 = SCM.getResource(&quot;touchscreenapp&quot;);&#xD;&#xA;                SCM.setStringValue(appname3,dep);  &#xD;&#xA;                var Res0 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;                var value0 = SCM.getIntValue(currentResource);&#xD;&#xA;                SCM.setIntValue(Res0,0);   &#xD;&#xA;                var Res1 = SCM.getResource(&quot;lcdapp/guilc001_erwcmousesupport&quot;);&#xD;&#xA;                SCM.setIntValue(Res1,1);&#xD;&#xA;                var Res2 = SCM.getResource(&quot;usbldapp/usbld001_irwrtos_mode&quot;);&#xD;&#xA;                SCM.setIntValue(Res2,0);&#xD;&#xA;                var Res3 = SCM.getResource(&quot;displaystring&quot;);&#xD;&#xA;                SCM.setIntValue(Res3,1);&#xD;&#xA;            }&#xD;&#xA;            function BackwardMapping()&#xD;&#xA;            {   &#xD;&#xA;              var Res0 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;              var value0 = SCM.getIntValue(Res0);&#xD;&#xA;           &#xD;&#xA;              if(value0 == 0) {&#xD;&#xA;                  SCM.setIntValue(currentResource,1);&#xD;&#xA;              } &#xD;&#xA;              else {&#xD;&#xA;                  SCM.setIntValue(currentResource,0);&#xD;&#xA;                } &#xD;&#xA;            } " URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_erwusbdevices/0" downWardmappedList="//@consumed.10 //@consumed.11 //@consumed.8 //@consumed.9 //@consumed.0 //@consumed.12 //@consumed.13 //@consumed.4" maxValue="2" minValue="0">
      <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
      <localValue xsi:type="ResourceModel:StringValue" value="0"/>
      <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
      <toolTipHelpDescription>This enables mouse support and allows user to use Mouse.</toolTipHelpDescription>
    </item>
    <item name="Use Keyboard" evalFunction="&#xD;&#xA;            function ForwardMapping()&#xD;&#xA;            {       &#xD;&#xA;                var dep = &quot;DependentApp&quot;;&#xD;&#xA;                var appname = SCM.getResource(&quot;keyboardapp&quot;);&#xD;&#xA;                SCM.setStringValue(appname,dep); &#xD;&#xA;                var appname1 = SCM.getResource(&quot;mouseapp&quot;); &#xD;&#xA;                SCM.setStringValue(appname1,dep); &#xD;&#xA;                var appname2 = SCM.getResource(&quot;usbldapp&quot;);&#xD;&#xA;                SCM.setStringValue(appname2,dep); &#xD;&#xA;                var appname3 = SCM.getResource(&quot;touchscreenapp&quot;);&#xD;&#xA;                SCM.setStringValue(appname3,dep);  &#xD;&#xA;                var Res0 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;                var value0 = SCM.getIntValue(currentResource);&#xD;&#xA;                SCM.setIntValue(Res0,1);  &#xD;&#xA;                var Res1 = SCM.getResource(&quot;lcdapp/guilc001_erwcmousesupport&quot;);&#xD;&#xA;                SCM.setIntValue(Res1,0);  &#xD;&#xA;                var Res2 = SCM.getResource(&quot;usbldapp/usbld001_irwrtos_mode&quot;);&#xD;&#xA;                SCM.setIntValue(Res2,0);    &#xD;&#xA;                var Res3 = SCM.getResource(&quot;displaystring&quot;);&#xD;&#xA;                SCM.setIntValue(Res3,2);&#xD;&#xA;                var Res4 = SCM.getResource(&quot;index3&quot;);  &#xD;&#xA;                if(value0 == 1) {&#xD;&#xA;                    SCM.setIntValue(Res4,0);&#xD;&#xA;                }  &#xD;&#xA;            }&#xD;&#xA;            function BackwardMapping()&#xD;&#xA;            {   &#xD;&#xA;              var Res0 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;              var value0 = SCM.getIntValue(Res0);&#xD;&#xA;               if(value0 == 1 ) {&#xD;&#xA;                  SCM.setIntValue(currentResource,1);&#xD;&#xA;              } &#xD;&#xA;              else {&#xD;&#xA;                  SCM.setIntValue(currentResource,0);&#xD;&#xA;              } &#xD;&#xA;            } " URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_erwusbdevices/1" downWardmappedList="//@consumed.11 //@consumed.10 //@consumed.8 //@consumed.9 //@consumed.0 //@consumed.12 //@consumed.13 //@consumed.4" maxValue="2" minValue="0">
      <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
      <localValue xsi:type="ResourceModel:StringValue" value="0"/>
      <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
      <toolTipHelpDescription>This enables Keyboard support and allows user to use Keyboard. </toolTipHelpDescription>
    </item>
  </provided>
  <provided xsi:type="ResourceModel:EnumerationParameter" name="TouchPad Device" evalFunction="&#xD;&#xA;          function ForwardMapping()&#xD;&#xA;          {       &#xD;&#xA;              var Res0 = SCM.getResource(&quot;index3&quot;);    &#xD;&#xA;              var value0 = SCM.getIntValue(currentResource);&#xD;&#xA;              SCM.setIntValue(Res0,value0);&#xD;&#xA;              var Res1 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;              var value1 = SCM.getIntValue(Res1);&#xD;&#xA;              var Res2 = SCM.getResource(&quot;lcdapp/guilc001_erwcmousesupport&quot;);&#xD;&#xA;              SCM.setIntValue(Res2,0);   &#xD;&#xA;      &#xD;&#xA;          }&#xD;&#xA;          function BackwardMapping()&#xD;&#xA;          {   &#xD;&#xA;              var Res0 = SCM.getResource(&quot;index3&quot;);    &#xD;&#xA;              var value0 = SCM.getIntValue(Res0);&#xD;&#xA;              SCM.setIntValue(currentResource,value0); &#xD;&#xA;              var Res1 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;              var value1 = SCM.getIntValue(Res1);&#xD;&#xA;          } " URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_erwusetouchscreen" downWardmappedList="//@consumed.2 //@consumed.12" multipleSelections="true">
    <defaultValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <localValue xsi:type="ResourceModel:StringValue" value="1"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <toolTipHelpDescription>This allows user to use TouchPad device. 
 Keyboard and TouchPad cannot be used together.
 Mouse and TouchPad can be used together.</toolTipHelpDescription>
    <item name="Use TouchPad" evalFunction="&#xD;&#xA;              function ForwardMapping(){&#xD;&#xA;              var dep = &quot;DependentApp&quot;;&#xD;&#xA;                var appname = SCM.getResource(&quot;keyboardapp&quot;);&#xD;&#xA;                SCM.setStringValue(appname,dep); &#xD;&#xA;                var appname1 = SCM.getResource(&quot;mouseapp&quot;); &#xD;&#xA;                SCM.setStringValue(appname1,dep); &#xD;&#xA;                var appname2 = SCM.getResource(&quot;usbldapp&quot;);&#xD;&#xA;                SCM.setStringValue(appname2,dep); &#xD;&#xA;                 var appname3 = SCM.getResource(&quot;touchscreenapp&quot;); &#xD;&#xA;                 SCM.setStringValue(appname3,dep); &#xD;&#xA;              var Res0 = SCM.getResource(&quot;index3&quot;);    &#xD;&#xA;              var value0 = SCM.getIntValue(currentResource);&#xD;&#xA;              SCM.setIntValue(Res0,value0);&#xD;&#xA;              var Res1 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;              var value1 = SCM.getIntValue(Res1);&#xD;&#xA;              var Res3 = SCM.getResource(&quot;displaystring1&quot;);&#xD;&#xA;              if(value0 == 1)&#xD;&#xA;              {&#xD;&#xA;                SCM.setIntValue(Res3,2); &#xD;&#xA;              }&#xD;&#xA;              else&#xD;&#xA;              {&#xD;&#xA;                SCM.setIntValue(Res3,0);    &#xD;&#xA;              }&#xD;&#xA;            }&#xD;&#xA;            function BackwardMapping(){&#xD;&#xA;                var Res0 = SCM.getResource(&quot;index3&quot;);    &#xD;&#xA;                var value0 = SCM.getIntValue(Res0);&#xD;&#xA;              &#xD;&#xA;                var Res1 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;                var value1 = SCM.getIntValue(Res1);&#xD;&#xA;                if(value1 == 1) {&#xD;&#xA;                    SCM.setIntValue(currentResource,0);&#xD;&#xA;                } &#xD;&#xA;                else {&#xD;&#xA;                     SCM.setIntValue(currentResource,value0);&#xD;&#xA;                } &#xD;&#xA;             }&#xD;&#xA;            " URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_erwusetouchscreen/0" downWardmappedList="//@consumed.11 //@consumed.10 //@consumed.8 //@consumed.9 //@consumed.2 //@consumed.5" maxValue="1" minValue="0">
      <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
      <localValue xsi:type="ResourceModel:StringValue" value="0"/>
      <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
      <toolTipHelpDescription>This allows user to use TouchPad device. 
 Keyboard and TouchPad cannot be used together.
 Mouse and TouchPad can be used together.</toolTipHelpDescription>
    </item>
  </provided>
  <provided xsi:type="ResourceModel:EnumerationParameter" name="No Available Devices" evalFunction="" URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_erwnodevices" multipleSelections="true">
    <defaultValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <localValue xsi:type="ResourceModel:StringValue" value="1"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="1"/>
    <toolTipHelpDescription>No devices available to use.
This option is selected when no device is available and Segger library is used for displaying purpose.</toolTipHelpDescription>
    <item name="No Devices Available  " evalFunction="&#xD;&#xA;              function ForwardMapping(){&#xD;&#xA;              var Res0 = SCM.getResource(&quot;index3&quot;);   &#xD;&#xA;              var Res1 = SCM.getResource(&quot;index1&quot;);   &#xD;&#xA;              var Res2 = SCM.getResource(&quot;index2&quot;);  &#xD;&#xA;              var value0 = SCM.getIntValue(Res0); &#xD;&#xA;              var value1 = SCM.getIntValue(Res1); &#xD;&#xA;              var value2 = SCM.getIntValue(Res2);&#xD;&#xA;              var value = SCM.getIntValue(currentResource);&#xD;&#xA;              var Res5 = SCM.getResource(&quot;displaystring1&quot;);&#xD;&#xA;&#xD;&#xA;              var Res4 = SCM.getResource(&quot;displaystring&quot;);&#xD;&#xA;              if(value == 1) {&#xD;&#xA;                    SCM.setIntValue(Res0,0);&#xD;&#xA;                    SCM.setIntValue(Res1,2);&#xD;&#xA;                    SCM.setIntValue(Res2,1);&#xD;&#xA;                    SCM.setIntValue(Res5,5);&#xD;&#xA;                     SCM.setIntValue(Res4,4);  &#xD;&#xA;             }  &#xD;&#xA;              else&#xD;&#xA;              {             &#xD;&#xA;                  SCM.setIntValue(Res4,6);  &#xD;&#xA;                  SCM.setIntValue(Res2,0);&#xD;&#xA;              }&#xD;&#xA;              var Res3 = SCM.getResource(&quot;lcdapp/guilc001_erwcmousesupport&quot;);&#xD;&#xA;              SCM.setIntValue(Res3,0);  &#xD;&#xA;&#xD;&#xA;  &#xD;&#xA;              var dep = &quot;DependentApp&quot;;&#xD;&#xA;              var appname = SCM.getResource(&quot;keyboardapp&quot;);&#xD;&#xA;              SCM.setStringValue(appname,dep); &#xD;&#xA;              var appname1 = SCM.getResource(&quot;mouseapp&quot;); &#xD;&#xA;              SCM.setStringValue(appname1,dep); &#xD;&#xA;              var appname2 = SCM.getResource(&quot;usbldapp&quot;);&#xD;&#xA;              SCM.setStringValue(appname2,dep); &#xD;&#xA;              var appname3 = SCM.getResource(&quot;touchscreenapp&quot;);&#xD;&#xA;              SCM.setStringValue(appname3,dep); &#xD;&#xA;            }&#xD;&#xA;            function BackwardMapping(){&#xD;&#xA;                var Res0 = SCM.getResource(&quot;index3&quot;);   &#xD;&#xA;                var Res1 = SCM.getResource(&quot;index1&quot;);    &#xD;&#xA;                var value0 = SCM.getIntValue(Res0); &#xD;&#xA;                var value1 = SCM.getIntValue(Res1); &#xD;&#xA;                var Res2 = SCM.getResource(&quot;index2&quot;); &#xD;&#xA;                var value2 = SCM.getIntValue(Res2); &#xD;&#xA;                if(value2 == 1) {&#xD;&#xA;                    SCM.setIntValue(currentResource,1);&#xD;&#xA;                }  &#xD;&#xA;                else&#xD;&#xA;                { &#xD;&#xA;                  SCM.setIntValue(currentResource,0);&#xD;&#xA;                }&#xD;&#xA;             }&#xD;&#xA;            " URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_erwnodevices/0" downWardmappedList="//@consumed.2 //@consumed.0 //@consumed.1 //@consumed.5 //@consumed.4 //@consumed.12 //@consumed.11 //@consumed.10 //@consumed.8 //@consumed.9" maxValue="1" minValue="0">
      <defaultValue xsi:type="ResourceModel:IntegerValue" value="1"/>
      <localValue xsi:type="ResourceModel:StringValue" value="1"/>
      <globalValue xsi:type="ResourceModel:IntegerValue" value="1"/>
      <toolTipHelpDescription>This option is selected when no device is available and Segger library is used for displaying purpose.</toolTipHelpDescription>
    </item>
  </provided>
  <provided xsi:type="ResourceModel:EnumerationParameter" name="Window Manager Configuration" URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_erwwinsupport" multipleSelections="true">
    <defaultValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <localValue xsi:type="ResourceModel:StringValue" value="1"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="1"/>
    <toolTipHelpDescription>This enables the optional window manager support.
When using the emWin window manager (WM), everything which appears on the display
 is contained in a window -- a rectangular area on the screen.</toolTipHelpDescription>
    <item name="Enable Window Manager" evalFunction=" function ForwardMapping()&#xD;&#xA;             {&#xD;&#xA;                var Res1 = SCM.getResource(&quot;index1&quot;);&#xD;&#xA;                var Intvalue1 = SCM.getIntValue(Res1);&#xD;&#xA;                var Res3 = SCM.getResource(&quot;index3&quot;);&#xD;&#xA;                var Res4 = SCM.getResource(&quot;index4&quot;);&#xD;&#xA;&#xD;&#xA;                var Intvalue3 = SCM.getIntValue(Res3);&#xD;&#xA;                var Intvalue2 = SCM.getIntValue(currentResource);&#xD;&#xA;                SCM.setIntValue(Res4,Intvalue2);&#xD;&#xA;                var Intvalue4 = SCM.getIntValue(Res4);&#xD;&#xA;                var Res5 = SCM.getResource(&quot;displaystring1&quot;);&#xD;&#xA;                if (Intvalue4 == 1)&#xD;&#xA;                {&#xD;&#xA;                    SCM.setIntValue(Res5,3);&#xD;&#xA;                }&#xD;&#xA;                else&#xD;&#xA;                {&#xD;&#xA;                    SCM.setIntValue(Res5,0); &#xD;&#xA;                }&#xD;&#xA;            }&#xD;&#xA;            function BackwardMapping()&#xD;&#xA;            {&#xD;&#xA;              var Res1 = SCM.getResource(&quot;index1&quot;);&#xD;&#xA;              var Intvalue1 = SCM.getIntValue(Res1);&#xD;&#xA;              var Res3 = SCM.getResource(&quot;index3&quot;);&#xD;&#xA;              var Intvalue3 = SCM.getIntValue(Res3);&#xD;&#xA;              var Res4 = SCM.getResource(&quot;index4&quot;);&#xD;&#xA;              var Intvalue4 = SCM.getIntValue(Res4);&#xD;&#xA;              if (Intvalue1 == 1 || Intvalue1 == 0  || Intvalue3 == 1 || Intvalue4 == 1 ) &#xD;&#xA;              {&#xD;&#xA;                SCM.setIntValue(currentResource,1);&#xD;&#xA;              }&#xD;&#xA;              else&#xD;&#xA;              {&#xD;&#xA;                SCM.setIntValue(currentResource,0);&#xD;&#xA;              } &#xD;&#xA;            }  &#xD;&#xA;            " URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_erwwinsupport/0" downWardmappedList="//@consumed.3 //@consumed.5" maxValue="1" minValue="0">
      <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
      <localValue xsi:type="ResourceModel:StringValue" value="0"/>
      <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
      <toolTipHelpDescription>This enables the optional window manager support.
When using the emWin window manager (WM), everything which appears on the display
 is contained in a window -- a rectangular area on the screen.
This option is mandatorily selected in presence of Mouse, Keyboard, Touch Pad.</toolTipHelpDescription>
    </item>
  </provided>
  <provided xsi:type="ResourceModel:IntegerParameter" name="RTOS Present " URI="http://www.infineon.com/1.0.22/app/guisl001/0/guisl001_rtos_present" maxValue="1" minValue="0">
    <defaultValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <localValue xsi:type="ResourceModel:StringValue" value="0"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="0"/>
    <toolTipHelpDescription>This allows a user to enable or disable RTOS</toolTipHelpDescription>
  </provided>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/index1" upWardMappingList="//@provided.1 //@provided.1/@item.0 //@provided.1/@item.1 //@provided.2 //@provided.2/@item.0 //@provided.3/@item.0 //@provided.4/@item.0" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="2"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="2"/>
    <requiredResource uriString="" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/index2" upWardMappingList="//@provided.3/@item.0" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <requiredResource uriString="" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/index3" upWardMappingList="//@provided.2 //@provided.2/@item.0 //@provided.3/@item.0 //@provided.4/@item.0" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <requiredResource uriString="" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/index4" upWardMappingList="//@provided.4/@item.0" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <requiredResource uriString="" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/displaystring" upWardMappingList="//@provided.0 //@provided.1/@item.0 //@provided.1/@item.1 //@provided.3/@item.0" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="4"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="4"/>
    <requiredResource uriString="" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/displaystring1" upWardMappingList="//@provided.0 //@provided.2/@item.0 //@provided.3/@item.0 //@provided.4/@item.0" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <requiredResource uriString="" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/lcdapp">
    <downWardmappedList xsi:type="ResourceModel:App" href="../../GUILC001/1.0.14/guilc001_0.app#/"/>
    <requiredResource uriString="app/guilc001/*" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/systimerapp">
    <downWardmappedList xsi:type="ResourceModel:App" href="../../SYSTM001/1.0.18/systm001_0.app#/"/>
    <requiredResource uriString="app/systm001/*" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" evalFunction="function resourceCondition() {&#xD;&#xA;            &#xD;&#xA;            var Res0 = Solver.getResource(&quot;index1&quot;);&#xD;&#xA;            var Val0 = Solver.getIntValue(Res0);&#xD;&#xA;            if ( (Val0 == 0) || (Val0 == 1)) {&#xD;&#xA;              return true;&#xD;&#xA;            }&#xD;&#xA;            &#xD;&#xA;            return false;&#xD;&#xA;        }" URI="http://www.infineon.com/1.0.22/app/guisl001/0/usbldapp" upWardMappingList="//@provided.1/@item.0 //@provided.1/@item.1 //@provided.2/@item.0 //@provided.3/@item.0">
    <localValue xsi:type="ResourceModel:StringValue" value="DependentApp"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="DependentApp"/>
    <requiredResource uriString="app/usbld001/*" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" evalFunction="function resourceCondition() {&#xD;&#xA;            var Res0 = Solver.getResource(&quot;guisl001_erwusetouchscreen/0&quot;);&#xD;&#xA;            var Val0 = Solver.getIntValue(Res0);&#xD;&#xA;            if (Val0 == 1 ) {&#xD;&#xA;              return true; &#xD;&#xA;            } &#xD;&#xA;            return false;&#xD;&#xA;        }" URI="http://www.infineon.com/1.0.22/app/guisl001/0/touchscreenapp" upWardMappingList="//@provided.1/@item.0 //@provided.1/@item.1 //@provided.2/@item.0 //@provided.3/@item.0">
    <localValue xsi:type="ResourceModel:StringValue" value="DependentApp"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="DependentApp"/>
    <requiredResource uriString="app/guits001/*" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" evalFunction="function resourceCondition() {&#xD;&#xA;            var Res0 = Solver.getResource(&quot;guisl001_erwusbdevices/0&quot;);&#xD;&#xA;            var Val0 = Solver.getIntValue(Res0);&#xD;&#xA;            if (Val0 == 1 ) {&#xD;&#xA;              return true; &#xD;&#xA;            } &#xD;&#xA;            return false;&#xD;&#xA;        }" URI="http://www.infineon.com/1.0.22/app/guisl001/0/mouseapp" upWardMappingList="//@provided.1/@item.0 //@provided.1/@item.1 //@provided.2/@item.0 //@provided.3/@item.0">
    <localValue xsi:type="ResourceModel:StringValue" value="DependentApp"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="DependentApp"/>
    <requiredResource uriString="app/guims001/*" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" evalFunction="function resourceCondition() {&#xD;&#xA;            var Res0 = Solver.getResource(&quot;guisl001_erwusbdevices/1&quot;);&#xD;&#xA;            var Val0 = Solver.getIntValue(Res0);&#xD;&#xA;            if (Val0 == 1) {&#xD;&#xA;              return true; &#xD;&#xA;            } &#xD;&#xA;            return false;&#xD;&#xA;        }" URI="http://www.infineon.com/1.0.22/app/guisl001/0/keyboardapp" upWardMappingList="//@provided.1/@item.0 //@provided.1/@item.1 //@provided.2/@item.0 //@provided.3/@item.0">
    <localValue xsi:type="ResourceModel:StringValue" value="DependentApp"/>
    <globalValue xsi:type="ResourceModel:StringValue" value="DependentApp"/>
    <requiredResource uriString="app/guikb001/*" uriType="LOCALTYPE"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/lcdapp/guilc001_erwcmousesupport" upWardMappingList="//@provided.1/@item.0 //@provided.1/@item.1 //@provided.2 //@provided.3/@item.0" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <downWardmappedList xsi:type="ResourceModel:IntegerParameter" href="../../GUILC001/1.0.14/guilc001_0.app#//@provided.0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/usbldapp/usbld001_irwrtos_mode" upWardMappingList="//@provided.1/@item.0 //@provided.1/@item.1" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="0"/>
  </consumed>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/usbldapp/usbld001_erwrtos_mode/0" isSystemDefined="true"/>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/clkapp/clk001_erwusbclkenable" isSystemDefined="true"/>
  <consumed xsi:type="ResourceModel:ProxyResource" URI="http://www.infineon.com/1.0.22/app/guisl001/0/systimerapp/systm001_systickinterval" isSystemDefined="true">
    <localValue xsi:type="ResourceModel:IntegerValue" value="1"/>
    <downWardmappedList xsi:type="ResourceModel:IntegerParameter" href="../../SYSTM001/1.0.18/systm001_0.app#//@provided.0"/>
    <globalValue xsi:type="ResourceModel:IntegerValue" value="1"/>
  </consumed>
  <propertyConstants name="uridevice" value="device/xmc4500/"/>
  <categoryDescription description="Middleware Apps" name="Middleware Apps">
    <subCategory description="Graphic" name="Graphic"/>
  </categoryDescription>
  <manifestInfo version="1.0.22">
    <keywords>emWin library</keywords>
    <keywords>Segger</keywords>
    <keywords>LCD</keywords>
    <keywords>Driver</keywords>
    <keywords>Keybord</keywords>
    <keywords>Mouse</keywords>
    <keywords>TouchPad</keywords>
    <keywords>Graphic</keywords>
    <keywords>GUISL001</keywords>
    <properties xsi:type="ResourceModel:AppProperties_1_0" singleton="true"/>
  </manifestInfo>
  <datagenerate fileName="GUISL001.h" fileType="HFILE" templateFileName="GUISL001.hdt" templateEngine="NONE" fileAction="COPY"/>
  <datagenerate fileName="Config" fileType="CDIR" templateFileName="Config" templateEngine="NONE" fileAction="COPY"/>
  <datagenerate fileName="GUISL001_Conf.h" fileType="HFILE" templateFileName="GUISL001_Confh.jet"/>
  <datagenerate fileName="GUISL001_Conf.c" templateFileName="GUISL001_Confc.jet"/>
  <datagenerate fileName="Dave/Generated/src/GUISL001/Config" fileType="HFILE" templateFileName="Dave/Generated/src/GUISL001/Config" templateEngine="NONE" fileAction="INCLUDE"/>
  <datagenerate fileName="guisl001" fileType="CLIB" templateFileName="guisl001" templateEngine="NONE" fileAction="INCLUDE" evalFunction="function preCondition()  {&#xD;&#xA;                  var Val1 = CG.getIntValue(&quot;guisl001_erwwinsupport/0&quot;);&#xD;&#xA;                  var Val2 = CG.getIntValue(&quot;guisl001_erwusbdevices/0&quot;);&#xD;&#xA;                  if ((Val1 == 1) &amp;&amp; (Val2 == 1))&#xD;&#xA;                  {&#xD;&#xA;&#xD;&#xA;                    return true;&#xD;&#xA;                  }&#xD;&#xA;                  else {&#xD;&#xA;                    &#xD;&#xA;                    return false;&#xD;&#xA;                  }&#xD;&#xA;                }"/>
  <datagenerate fileName="guisl001_WithoutMouse" fileType="CLIB" templateFileName="guisl001_WithoutMouse" templateEngine="NONE" fileAction="INCLUDE" evalFunction="function preCondition()  {&#xD;&#xA;                  var Val1 = CG.getIntValue(&quot;guisl001_erwwinsupport/0&quot;);&#xD;&#xA;                  var Val2 = CG.getIntValue(&quot;guisl001_erwusbdevices/0&quot;);&#xD;&#xA;                  var Val3 = CG.getIntValue(&quot;guisl001_erwusetouchscreen/0&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  var value1 = CG.getSoftwareId().substring(0,1).compareTo(&quot;4&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  if( value1 == 0 )&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  {&#xD;&#xA;                  &#x9;if (((Val1 == 1) &amp;&amp; (Val2 == 0)) || ((Val1 == 1) &amp;&amp; (Val3 == 1) &amp;&amp; (Val2 == 0)))&#xD;&#xA;                  &#x9;{&#xD;&#xA;                    &#x9;return true;&#xD;&#xA;                  &#x9;}&#xD;&#xA;                  &#x9;else {&#xD;&#xA;                        return false;&#xD;&#xA;                  &#x9;}&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  }&#xD;&#xA;                     return false;&#xD;&#xA;                }"/>
  <datagenerate fileName="guisl001_WithoutMouse_WithoutWin" fileType="CLIB" templateFileName="guisl001_WithoutMouse_WithoutWin" templateEngine="NONE" fileAction="INCLUDE" evalFunction="function preCondition()  {&#xD;&#xA;                  var Val1 = CG.getIntValue(&quot;guisl001_erwwinsupport/0&quot;);&#xD;&#xA;                  var Val2 = CG.getIntValue(&quot;guisl001_erwusbdevices/0&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  var value1 = CG.getSoftwareId().substring(0,1).compareTo(&quot;4&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  if( value1 == 0 )&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  {&#xD;&#xA;&#x9;                  if ((Val1 == 0) &amp;&amp; (Val2 == 0))&#xD;&#xA;&#x9;                  {&#xD;&#xA;&#x9;                   return true;&#xD;&#xA;&#x9;                  }&#xD;&#xA;&#x9;                  else {&#xD;&#xA;&#x9;&#xD;&#xA;&#x9;                    return false;&#xD;&#xA;&#x9;                  }&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  }&#xD;&#xA;      &#x9;&#x9;    return false;&#xD;&#xA;                }"/>
  <datagenerate fileName="guisl001_xmc1" fileType="CLIB" templateFileName="guisl001_xmc1" templateEngine="NONE" fileAction="INCLUDE" evalFunction="function preCondition()  {&#xD;&#xA;                  var Val1 = CG.getIntValue(&quot;guisl001_erwwinsupport/0&quot;);&#xD;&#xA;                  var Val2 = CG.getIntValue(&quot;guisl001_erwusbdevices/0&quot;);&#xD;&#xA;                  var Val3 = CG.getIntValue(&quot;guisl001_erwusetouchscreen/0&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  var value1 = CG.getSoftwareId().substring(0,1).compareTo(&quot;1&quot;);&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  if( value1 == 0 )&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  {&#xD;&#xA;                  &#x9;if (((Val1 == 0) &amp;&amp; (Val2 == 0)) || &#xD;&#xA;&#x9;&#x9;&#x9;&#x9;&#x9;&#x9;((Val1 == 1) &amp;&amp; (Val2 == 0)) || &#xD;&#xA;&#x9;&#x9;&#x9;&#x9;&#x9;&#x9;((Val1 == 1) &amp;&amp; (Val3 == 0) &amp;&amp; (Val2 == 0)))&#xD;&#xA;                  &#x9;{&#xD;&#xA;                    &#x9;return true;&#xD;&#xA;                  &#x9;}&#xD;&#xA;                  &#x9;else {&#xD;&#xA;                        return false;&#xD;&#xA;                  &#x9;}&#xD;&#xA;&#x9;&#x9;&#x9;&#x9;  }&#xD;&#xA;                     return false;&#xD;&#xA;                }"/>
  <datagenerate fileName="m" fileType="CLIB" templateFileName="libm" templateEngine="NONE" fileAction="INCLUDE"/>
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
