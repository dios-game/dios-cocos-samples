@echo off 

rem -- 用户手动配置

rem -------------------------------
rem -- ANDROID
rem -------------------------------
set JAVA_HOME=C:\Program Files\Java\jdk1.7.0_40
set ECLIPSE_HOME=E:\adt-bundle-windows-x86\eclipse
set ANDROID_SDK_HOME=E:\adt-bundle-windows-x86\sdk
set ANDROID_NDK_HOME=E:\android-ndk-r10e
set ANTBIN=%ECLIPSE_HOME%\plugins\org.apache.ant_1.9.2.v201404171502\bin
set DIOS_CMAKE_V3=true

rem -------------------------------
rem -- Tools
rem -------------------------------
set TEXTURE_PACKER_PATH=E:\TexturePacker\bin

rem -------------------------------
rem -- DIOS 变量
rem -------------------------------
set DIOS_PROJECT_PATH=%~dp0
set DIOS_PATH=%DIOS_PROJECT_PATH%\dios-cocos\dios
set DIOS_COCOS_PATH=%DIOS_PROJECT_PATH%\dios-cocos\src\oslibs\cocos\cocos-src

rem -- 系统自动配置
rem -------------------------------
rem -- ANDROID
rem -------------------------------
set ANDROID_TOOLS=%ANDROID_SDK_HOME%\tools
set ANDROID_SDK_PLATFORM_TOOLS=%ANDROID_SDK_HOME%;%ANDROID_SDK_HOME%\platform-tools
set ANDROID_SDK_TOOLS=%ANDROID_SDK_HOME%\tools
set NDK_MODULE_PATH=%~dp0;%ANDROID_NDK_HOME%\sources\;
set NDK_MODULE_PATH=%DIOS_COCOS_PATH%;%DIOS_COCOS_PATH%/external;%DIOS_COCOS_PATH%/cocos;%NDK_MODULE_PATH%
set NDK_MODULE_PATH=%NDK_MODULE_PATH:\=/%
set PATH=%PATH%;%JAVA_HOME%\bin;%ANTBIN%;%ANDROID_NDK_HOME%;%ANDROID_SDK_PLATFORM_TOOLS%;%ANDROID_SDK_TOOLS%;%DIOS_PATH%\build\tools\win
set CLASSPATH=.;%JAVA_HOME%\lib
set ANDROID_HOME=%ANDROID_SDK_HOME%
set ANDROID_NDK=%ANDROID_NDK_HOME%

rem -------------------------------
rem -- DIOS 变量
rem -------------------------------
set DIOS_INSTALL=%DIOS_PROJECT_PATH%\install
set DIOS_TOOLS=%DIOS_PATH%\build\tools\win
set DIOS_CMAKE=%DIOS_PATH%\build\cmake

rem -------------------------------
rem -- DIOS Compiler
rem -------------------------------
if defined VS140COMNTOOLS (
	SET DIOS_COMPILER_TOOLS="%VS140COMNTOOLS%"
	SET DIOS_COMPILER=vc14
	if !DIOS_CMAKE_V3!==true (
		SET DIOS_GENERATOR_X86="Visual Studio 14 2015"
		SET DIOS_GENERATOR_X64="Visual Studio 14 2015 Win64"	
	) else (
		SET DIOS_GENERATOR_X86="Visual Studio 14"
		SET DIOS_GENERATOR_X64="Visual Studio 14 Win64"		
	)
) else if defined VS120COMNTOOLS (
	SET DIOS_COMPILER_TOOLS="%VS120COMNTOOLS%"
	SET DIOS_COMPILER=vc12
	if !DIOS_CMAKE_V3!==true (
		SET DIOS_GENERATOR_X86="Visual Studio 12 2013"
		SET DIOS_GENERATOR_X64="Visual Studio 12 2013 Win64"	
	) else (
		SET DIOS_GENERATOR_X86="Visual Studio 12"
		SET DIOS_GENERATOR_X64="Visual Studio 12 Win64"		
	)
) else if defined VS110COMNTOOLS (
	SET DIOS_COMPILER_TOOLS="%VS110COMNTOOLS%"
	SET DIOS_COMPILER=vc11
	if !DIOS_CMAKE_V3!==true (
		SET DIOS_GENERATOR_X86="Visual Studio 11 2012"
		SET DIOS_GENERATOR_X64="Visual Studio 11 2012 Win64"	
	) else (
		SET DIOS_GENERATOR_X86="Visual Studio 11"
		SET DIOS_GENERATOR_X64="Visual Studio 11 Win64"		
	)
) else if defined VS100COMNTOOLS (
	SET DIOS_COMPILER_TOOLS="%VS100COMNTOOLS%"
	SET DIOS_COMPILER=vc10
	if !DIOS_CMAKE_V3!==true (
		SET DIOS_GENERATOR_X86="Visual Studio 10 2010"
		SET DIOS_GENERATOR_X64="Visual Studio 10 2010 Win64"	
	) else (
		SET DIOS_GENERATOR_X86="Visual Studio 10"
		SET DIOS_GENERATOR_X64="Visual Studio 10 Win64"		
	)
)
call %DIOS_COMPILER_TOOLS%vsvars32.bat