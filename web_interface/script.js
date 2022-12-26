const serverUrl = 'http://192.168.1.14'

const buttons = document.querySelectorAll('button');
buttons.forEach(button => {
  button.addEventListener('click', event => {
    const command = event.target.id;
    sendCommand(command);
  });
});

var btn = document.getElementById("LCD Data");
// add event listener for the button, for action "click"
btn.addEventListener("click", sendData);

function sendData() {
  const textbox = document.getElementById("TextBox").value;
  document.getElementById("status").innerHTML = 'Sent "' + textbox + '" to LCD';
  url = serverUrl + "/lcd?content=" + textbox;
  const xhr = new XMLHttpRequest();
  xhr.open('GET', url, true);
  xhr.send(null);

}

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