$StartMosquitto = $true
$MosquittoExe  = "C:\Program Files\Mosquitto\mosquitto.exe"
$MosquittoConf = "C:\Program Files\Mosquitto\mosquitto.conf"
$NodeRedCmd    = "$env:APPDATA\npm\node-red.cmd"
$EditorUrl     = "http://127.0.0.1:1880"
$DashboardUrl  = "http://127.0.0.1:1880/ui"
$WaitSeconds   = 60

function Test-PortOpen { 
    param($Port)
    try { 
        Get-NetTCPConnection -State Listen -LocalPort $Port -ErrorAction Stop | Out-Null
        return $true 
    }
    catch { 
        return $false 
    }
}

function Wait-HttpOk { 
    param($Url, $TimeoutSec = 30)
    $sw = [Diagnostics.Stopwatch]::StartNew()
    while ($sw.Elapsed.TotalSeconds -lt $TimeoutSec) {
        try {
            $r = Invoke-WebRequest -Uri $Url -UseBasicParsing -TimeoutSec 3
            if ($r.StatusCode -ge 200 -and $r.StatusCode -lt 500) { 
                return $true 
            }
        } catch {}
        Start-Sleep 1
    }
    return $false
}

# Force-start Mosquitto in foreground
try { net stop mosquitto | Out-Null } catch {}
Start-Sleep 1
Start-Process -FilePath "C:\Program Files\Mosquitto\mosquitto.exe" -ArgumentList @("-c", "C:\Program Files\Mosquitto\mosquitto.conf") -WindowStyle Minimized
Start-Sleep 2

if (-not (Get-Process -Name "node-red" -ErrorAction SilentlyContinue)) {
    Start-Process -FilePath $NodeRedCmd -WindowStyle Minimized
}

if (Wait-HttpOk -Url $EditorUrl -TimeoutSec $WaitSeconds) {
    Start-Process $DashboardUrl
} else {
    Write-Host "Node-RED not responding in $WaitSeconds s. Opening editor."
    Start-Process $EditorUrl
}

# Run to test (keeps window open):
# powershell -NoExit -ExecutionPolicy Bypass -File "C:\Thermostat\scripts\Start-ThermostatDashboard.ps1"

