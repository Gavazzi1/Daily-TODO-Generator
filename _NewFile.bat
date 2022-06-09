@echo off

set fn=%date:~-4,4%-%date:~-10,2%-%date:~7,2%.txt

for /f %%a in ('wmic path win32_localtime get dayofweek /format:list ^| findstr "="') do (set %%a)

echo Todo: >> %fn%

if %DayOfWeek% == 5 (
  echo.>> %fn%
  echo Submit timesheet >> %fn%)

echo.>> %fn%
echo.>> %fn%


echo Done: >> %fn%
echo.>> %fn%
echo.>> %fn%


echo Notes: >> %fn%
echo.>> %fn%
