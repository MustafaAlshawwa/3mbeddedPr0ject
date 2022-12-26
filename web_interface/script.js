const serverUrl = 'http://127.0.0.1:8000'; // Replace with the IP address of your NodeMCU

const buttons = document.querySelectorAll('button');
buttons.forEach(button => {
  button.addEventListener('click', event => {
    const command = event.target.id;
    sendCommand(command);
  });
});

function sendCommand(command) {
  document.getElementById("status").innerHTML = command;
  const xhr = new XMLHttpRequest();
  xhr.open('GET', `${serverUrl}/${command}`, true);
  xhr.send(null);
}

  // Add event listeners to the document to listen for key presses
  document.addEventListener('keydown', event => {
    // Check which key was pressed and send the corresponding command
    switch (event.key) {
      case 'ArrowUp':
        sendCommand('forward');
        break;
      case 'ArrowLeft':
        sendCommand('left');
        break;
      case 'ArrowRight':
        sendCommand('right');
        break;
      case 'ArrowDown':
        sendCommand('reverse');
        break;
      default:
        break;
    }
  });