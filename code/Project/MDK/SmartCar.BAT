SET PATH=D:\Software\keil5\ARM\ARMCC\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\NVIDIA Corporation\NVIDIA NGX;C:\Program Files\dotnet\;C:\Users\yasaburo\AppData\Local\Microsoft\WindowsApps;D:\Software\bandizip\;C:\Users\yasaburo\AppData\Local\GitHubDesktop\bin
SET CPU_TYPE=SKEAZ128xxx4
SET CPU_VENDOR=NXP
SET UV2_TARGET=SmartCar
SET CPU_CLOCK=0x00B71B00
"D:\Software\keil5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_skeaz1284._ia"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_skeaz1284.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\adc.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\ftm.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\i2c.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\ics.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\pit.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\common.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\spi.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\kea128_irq.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\uart.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\control.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\init.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\signal.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\mpu6050.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\delay.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lcd.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\oled.__i"
"D:\Software\keil5\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\SmartCar.lnp"
"D:\Software\keil5\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\SmartCar.axf" --i32combined --output ".\Objects\SmartCar.hex"
