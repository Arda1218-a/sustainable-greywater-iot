// Initialize date and time
function updateClock() {
    const now = new Date();
    document.getElementById('current-time').textContent = now.toLocaleTimeString('tr-TR', { hour12: false });
    document.getElementById('current-date').textContent = now.toLocaleDateString('tr-TR', { day: '2-digit', month: 'short', year: 'numeric' });
}
setInterval(updateClock, 1000);
updateClock();

// --- Tank Timers ---
const tankTimers = {
    1: { seconds: 7200, auto: true },
    2: { seconds: 5400, auto: true },
    3: { seconds: 3600, auto: true },
    4: { seconds: 1800, auto: true }
};

// Load preferences from local storage
for (let i = 1; i <= 4; i++) {
    const savedAuto = localStorage.getItem(`t${i}-auto`);
    if (savedAuto !== null) {
        tankTimers[i].auto = savedAuto === 'true';
        document.getElementById(`t${i}-auto`).checked = tankTimers[i].auto;
    }
}

function formatTime(totalSeconds) {
    const h = Math.floor(totalSeconds / 3600).toString().padStart(2, '0');
    const m = Math.floor((totalSeconds % 3600) / 60).toString().padStart(2, '0');
    const s = (totalSeconds % 60).toString().padStart(2, '0');
    return `${h}:${m}:${s}`;
}

function updateTimers() {
    for (let i = 1; i <= 4; i++) {
        if (tankTimers[i].seconds > 0) {
            tankTimers[i].seconds--;
        } else {
            if (tankTimers[i].auto) {
                mixTank(i); // Auto mix when timer reaches 0
            } else {
                showToast(`Tank ${i} karıştırma süresi doldu!`, 'warning');
                tankTimers[i].seconds = 7200; // Reset just to avoid negative, wait for manual
            }
        }
        
        const timerEl = document.getElementById(`t${i}-timer`);
        timerEl.textContent = formatTime(tankTimers[i].seconds);
        
        // Highlight in orange if < 15 mins (900 seconds)
        if (tankTimers[i].seconds < 900) {
            timerEl.classList.add('warning');
        } else {
            timerEl.classList.remove('warning');
        }
    }
}
setInterval(updateTimers, 1000);

function mixTank(tankId) {
    tankTimers[tankId].seconds = 7200; // Reset to 2 hours
    showToast(`Tank ${tankId} karıştırılıyor...`, 'info');
    // Animate water level slightly to simulate mixing
    const levelEl = document.getElementById(`t${tankId}-level`);
    const currentHeight = levelEl.style.height;
    levelEl.style.height = '100%';
    setTimeout(() => {
        levelEl.style.height = currentHeight;
    }, 1500);
}

function toggleAutoMix(tankId) {
    const isAuto = document.getElementById(`t${tankId}-auto`).checked;
    tankTimers[tankId].auto = isAuto;
    localStorage.setItem(`t${tankId}-auto`, isAuto);
    showToast(`Tank ${tankId} otomatik karıştırma: ${isAuto ? 'Açık' : 'Kapalı'}`, 'info');
}

// --- Live Data Simulation ---
const tankData = {
    1: { vol: 1500, max: 2000 },
    2: { vol: 1500, max: 2000 },
    3: { vol: 1500, max: 2000 },
    4: { vol: 1500, max: 2000 }
};

function simulateLiveData() {
    // Fluctuating Tank levels
    for (let i = 1; i <= 4; i++) {
        // Random change between -5 and +5 liters
        const change = Math.floor(Math.random() * 11) - 5;
        tankData[i].vol += change;
        
        // Clamp
        if (tankData[i].vol < 0) tankData[i].vol = 0;
        if (tankData[i].vol > tankData[i].max) tankData[i].vol = tankData[i].max;
        
        document.getElementById(`t${i}-vol`).textContent = tankData[i].vol;
        document.getElementById(`t${i}-weight`).textContent = tankData[i].vol; // 1L = 1kg
        
        const percentage = (tankData[i].vol / tankData[i].max) * 100;
        document.getElementById(`t${i}-level`).style.height = `${percentage}%`;
    }

    // Fluctuating Sensors
    const ph = (7.2 + (Math.random() * 0.2 - 0.1)).toFixed(2);
    document.getElementById('val-ph').textContent = ph;
    const phCircle = document.getElementById('ph-circle');
    if (ph < 6.5 || ph > 8.5) phCircle.style.borderColor = 'rgba(239, 68, 68, 0.5)';
    else phCircle.style.borderColor = 'rgba(74, 222, 128, 0.5)';

    document.getElementById('val-tds').textContent = Math.floor(340 + (Math.random() * 10 - 5));
    document.getElementById('val-turb').textContent = Math.floor(12 + (Math.random() * 2 - 1));
    document.getElementById('val-temp').textContent = (24.5 + (Math.random() * 0.4 - 0.2)).toFixed(1);
}
setInterval(simulateLiveData, 2000);

// --- Process Flow Animation ---
function rotateProcess() {
    const processes = document.querySelectorAll('.flow-nodes .process');
    let activeIndex = 0;
    processes.forEach((p, idx) => {
        if (p.classList.contains('active')) {
            activeIndex = idx;
            p.classList.remove('active');
        }
    });
    
    activeIndex = (activeIndex + 1) % processes.length;
    processes[activeIndex].classList.add('active');
}
setInterval(rotateProcess, 3000);

// --- Modal ---
function openModal() {
    document.getElementById('add-water-modal').classList.add('active');
}

function closeModal() {
    document.getElementById('add-water-modal').classList.remove('active');
}

function submitWater() {
    showToast('Harici su başarıyla karantina tankına (T3) yönlendirildi.', 'success');
    closeModal();
    // Simulate increase in T3
    tankData[3].vol = Math.min(tankData[3].max, tankData[3].vol + 200);
}

function startQuarantinePurify() {
    showToast('T3 Karantina Arıtma döngüsü başlatıldı. Kalite kontrolü yapılıyor...', 'info');
}

// --- Toast Notifications ---
function showToast(message, type = 'info') {
    const container = document.getElementById('toast-container');
    const toast = document.createElement('div');
    toast.className = `toast`;
    
    let icon = 'ℹ️';
    if (type === 'success') icon = '✅';
    if (type === 'warning') icon = '⚠️';
    if (type === 'error') icon = '❌';

    toast.innerHTML = `${icon} ${message}`;
    container.appendChild(toast);
    
    setTimeout(() => {
        toast.style.opacity = '0';
        setTimeout(() => toast.remove(), 300);
    }, 4000);
}
