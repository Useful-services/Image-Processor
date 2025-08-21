const inputEl = document.getElementById('inputText');
const btnEl = document.getElementById('sendBtn');
const textOutput = document.getElementById('text-output');
const statusEl = document.getElementById('status');

const backend_url = 'http://localhost:8080'

function setStatus(text) {
  if (statusEl)
    statusEl.textContent = text;
}
async function sendText() {
  if (!inputEl || !textOutput)
    return;
  const text = inputEl.value.trim();
  if (text.length === 0) {
    textOutput.textContent = 'Введите текст.';
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
    textOutput.textContent = data['reversed'];
    setStatus('Готово');
  } catch (err) {
    textOutput.textContent = 'Ошибка: ' + err.message;
    setStatus('Ошибка');
  }
}
if (btnEl) {
  btnEl.addEventListener('click', () => {
    void sendText();
  });
}

const imageInput = document.getElementById('imageInput');
const sendImageBtn = document.getElementById('sendImageBtn');
const originalImage = document.getElementById('originalImage');
const processedImage = document.getElementById('processedImage');
const imageOutput = document.getElementById('image-output');

async function processImage(file) {
  if (!file) {
    imageOutput.textContent = 'Выберите изображение';
    return;
  }

  setStatus('Загрузка изображения...');

  try {
    const reader = new FileReader();

    reader.onload = async function(e) {
      const base64 = e.target.result.split(',')[1];

      setStatus('Отправка на сервер...');

      try {
        const response = await fetch(backend_url + '/process-image', {
          method: 'POST',
          headers: {'Content-Type': 'application/json'},
          body: JSON.stringify({image: base64})
        });

        if (!response.ok) {
          throw new Error('HTTP Error! status: ' + response.status);
        }
        
        const data = await response.json();

        processedImage.src = 'data:image/png;base64,' + data.processed_image;
        processedImage.style.display = 'block';

        imageOutput.textContent = JSON.stringify({
          width: data.width,
          height: data.height,
          channels: data.channels
        }, null, 2);

        setStatus('Готово');

      } catch (err) {
        console.error('Error: ' + err);
        imageOutput.textContent = 'Ошибка: ' + err.message;
        setStatus('Ошибка');
      }
    };
    reader.readAsDataURL(file);
  } catch (err) {
    imageOutput.textContent = 'Ошибка чтения файла: ' + err.message;
    setStatus('Ошибка');
  }
}

imageInput.addEventListener('change', function(e) {
  const file = e.target.files[0];
  if (file) {
    const reader = new FileReader();
    reader.onload = function (e) {
      originalImage.src = e.target.result;
      originalImage.style.display = 'block';
    };
    reader.readAsDataURL(file);
  }
  processedImage.src = '';
  imageOutput.textContent = '-';
});

sendImageBtn.addEventListener('click', function() {
  const file = imageInput.files[0];
  processImage(file);
});