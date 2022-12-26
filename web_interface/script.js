const serverUrl = 'http://127.0.0.1:8000'; // Replace with the IP address of your NodeMCU

const buttons = document.querySelectorAll('button');
buttons.forEach(button => {
  button.addEventListener('click', event => {
    const command = event.target.id;
    sendCommand(command);
  });
});

function sendCommand(command) {
  const xhr = new XMLHttpRequest();
  xhr.open('GET', `${serverUrl}/${command}`, true);
  xhr.send(null);
}
