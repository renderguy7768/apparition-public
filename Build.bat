@echo off
REM This little script will build the solution four times, in each Configuation+Platform. The build logs are in log files.

REM Btw for those who don't know, lines starting with "REM" are comments. Yeah, I was confused too. You're welcome.

REM CHANGE THIS :: Set this path to be the path to your MSBuild.exe file. It should look something like the path below.
SET msbuild="C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe"

REM Setting the solution to be built from command line args. You could alternatively switch it out to just be your .sln file and not need to keep passing in arguments.
SET slnfile="apparition.sln"

REM Variables
SET bit64=64
SET bit32=86
SET debug=Debug
SET release=Release
SET logfilenameprefix=BuildLog_
SET logfilenamesuffix=.log
SET resultfilename=BuildResults.log
SET successmessageprefix=Successfully built
SET failuremessageprefix=Failed to build

(%msbuild% %slnfile% /p:Configuration=%debug% /p:Platform=x%bit64% /flp:logfile=%logfilenameprefix%%debug%_%bit64%%logfilenamesuffix% && ECHO "%successmessageprefix% %debug% x%bit64%" > %resultfilename%) || ECHO "%failuremessageprefix% %debug% x%bit64%" > %resultfilename%


(%msbuild% %slnfile% /p:Configuration=%release% /p:Platform=x%bit64% /flp:logfile=%logfilenameprefix%%release%_%bit64%%logfilenamesuffix% && ECHO "%successmessageprefix% %release% x%bit64%" >> %resultfilename%) || ECHO "%failuremessageprefix% %release% x%bit64%" >> %resultfilename%


(%msbuild% %slnfile% /p:Configuration=%debug% /p:Platform=x%bit32% /flp:logfile=%logfilenameprefix%%debug%_%bit32%%logfilenamesuffix% && ECHO "%successmessageprefix% %debug% x%bit32%" >> %resultfilename%) || ECHO "%failuremessageprefix% %debug% x%bit32%" >> %resultfilename%


(%msbuild% %slnfile% /p:Configuration=%release% /p:Platform=x%bit32% /flp:logfile=%logfilenameprefix%%release%_%bit32%%logfilenamesuffix% && ECHO "%successmessageprefix% %release% x%bit32%" >> %resultfilename%) || ECHO "%failuremessageprefix% %release% x%bit32%" >> %resultfilename%

pause