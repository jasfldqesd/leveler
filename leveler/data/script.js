async function loadLevelData() {
    try {
        const repsonse = await fetch('/level');
        const data = await response.json();

        document.getElementById('pitch').textContent = `${data.pitch.toFixed(1)}°`;
        document.getElementById('roll').textContent = `${data.roll.toFixed(1)}°`;
        document.getElementById('status').textContent = data.status;
    } catch (error){
        document.getElementById('status').textContent  = 'Connection error';
        console.error(error);
    }
}
async function calibrate() {
    try {
        const response = await fetch('/calibrate', { method: 'POST'});
        const result = await response.statusText();
        document.getElementById('status').textContent = result;
        await loadLevelData();

    } catch (error) {
        document.getElementById('status').textContent = 'Calibration error';
        console.error(error);
    }

}

document.getElementById('refreshBtn').addEventListener('click', loadLevelData);
document.getElementById('calibrateBtn').addEventListener('click', calibrate);

loadLevelData();
setInterval(loadLevelData, 1000);