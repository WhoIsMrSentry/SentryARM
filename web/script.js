const videoElement = document.getElementById('video');
const canvasElement = document.getElementById('output');
const canvasCtx = canvasElement.getContext('2d');

// WebSocket hedef (ESP32 AP varsayılan IP)
const WS_IP = '192.168.4.1';
const WS_PORT = 81;
let ws = null;

function connectWS() {
  try {
    ws = new WebSocket(`ws://${WS_IP}:${WS_PORT}`);
    ws.onopen = () => console.log('WebSocket connected');
    ws.onclose = () => { console.log('WebSocket closed'); setTimeout(connectWS, 1000); };
    ws.onerror = (e) => console.log('WebSocket error', e);
  } catch (e) {
    console.log('WS connection failed', e);
    setTimeout(connectWS, 1000);
  }
}
connectWS();

const hands = new Hands({locateFile: (file) => {
  return `https://cdn.jsdelivr.net/npm/@mediapipe/hands/${file}`;
}});

hands.setOptions({
  maxNumHands: 1,
  modelComplexity: 1,
  minDetectionConfidence: 0.7,
  minTrackingConfidence: 0.6
});

hands.onResults(results => {
  canvasCtx.save();
  canvasCtx.clearRect(0, 0, canvasElement.width, canvasElement.height);
  canvasCtx.drawImage(results.image, 0, 0, canvasElement.width, canvasElement.height);
  if (results.multiHandLandmarks && results.multiHandLandmarks.length > 0) {
    for (const landmarks of results.multiHandLandmarks) {
      drawConnectors(canvasCtx, landmarks, HAND_CONNECTIONS, {color: '#00FF00', lineWidth: 2});
      drawLandmarks(canvasCtx, landmarks, {color: '#FF0000', lineWidth: 1});
    }
  }
  canvasCtx.restore();
  // Eğer el bulunduysa açılar hesaplanıp WebSocket ile gönderilir
  if (results.multiHandLandmarks && results.multiHandLandmarks.length > 0 && ws && ws.readyState === WebSocket.OPEN) {
    const lm = results.multiHandLandmarks[0];
    function angleBetween(a, b, c) {
      const v1x = a.x - b.x, v1y = a.y - b.y;
      const v2x = c.x - b.x, v2y = c.y - b.y;
      const dot = v1x * v2x + v1y * v2y;
      const m1 = Math.hypot(v1x, v1y);
      const m2 = Math.hypot(v2x, v2y);
      if (m1 === 0 || m2 === 0) return 0;
      const cos = Math.max(-1, Math.min(1, dot / (m1 * m2)));
      return Math.acos(cos) * 180.0 / Math.PI;
    }
    const angs = [];
    angs[0] = Math.round(angleBetween(lm[2], lm[3], lm[4]));   // thumb
    angs[1] = Math.round(angleBetween(lm[5], lm[6], lm[8]));   // index
    angs[2] = Math.round(angleBetween(lm[9], lm[10], lm[12])); // middle
    angs[3] = Math.round(angleBetween(lm[13], lm[14], lm[16])); // ring
    angs[4] = Math.round(angleBetween(lm[17], lm[18], lm[20])); // pinky
    ws.send(angs.join(','));
  }
});

const camera = new Camera(videoElement, {
  onFrame: async () => {
    await hands.send({image: videoElement});
  },
  width: 640,
  height: 480
});
camera.start();
