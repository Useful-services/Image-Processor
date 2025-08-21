export {};

const inputEl = document.getElementById('inputText') as HTMLTextAreaElement | null;
const btnEl = document.getElementById('sendBtn') as HTMLButtonElement | null;
const outputEl = document.getElementById('output') as HTMLElement | null;
const statusEl = document.getElementById('status') as HTMLElement | null;

function setStatus(text: string) {
  if (statusEl) statusEl.textContent = text;
}

async function sendText() {
  if (!inputEl || !outputEl) return;
  const text = inputEl.value.trim();
  if (text.length === 0) {
    outputEl.textContent = 'Введите текст.';
    return;
  }
  setStatus('Отправка...');
  try {
    const response = await fetch('http://localhost:8080/process-text', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ text })
    });
    const data = await response.json();
    outputEl.textContent = JSON.stringify(data, null, 2);
    setStatus('Готово');
  } catch (err) {
    outputEl.textContent = 'Ошибка: ' + (err as Error).message;
    setStatus('Ошибка');
  }
}

if (btnEl) {
  btnEl.addEventListener('click', () => {
    void sendText();
  });
}

