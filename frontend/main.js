const inputEl = document.getElementById('inputText');
const btnEl = document.getElementById('sendBtn');
const outputEl = document.getElementById('output');
const statusEl = document.getElementById('status');

const backend_url = 'http://localhost:8080'

function setStatus(text) {
  if (statusEl)
    statusEl.textContent = text;
}
async function sendText() {
  if (!inputEl || !outputEl)
    return;
  const text = inputEl.value.trim();
  if (text.length === 0) {
    outputEl.textContent = 'Введите текст.';
    return;
  }
  setStatus('Отправка...');
  try {
    console.log(JSON.stringify({ text }))
    const response = await fetch(backend_url + '/process-text', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ text })
    });
    const data = await response.json();
    outputEl.textContent = data['reversed'];
    setStatus('Готово');
  } catch (err) {
    outputEl.textContent = 'Ошибка: ' + err.message;
    setStatus('Ошибка');
  }
}
if (btnEl) {
  btnEl.addEventListener('click', () => {
    void sendText();
  });
}

async function test() {
  const resp = await fetch(backend_url + '/status', {
    mode: "no-cors"
  });
  if (resp.ok) {
    outputEl.textContent = JSON.stringify(await resp.json); 
  } else {
    alert("Ошибка HTTP: " + resp.status)
  }
}
