let last_used_command = "a";
const serverUrl = 'http://192.168.1.100'

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
  for (let i = 0; i < 10; i++)
  {
    xhr.open('GET', `${serverUrl}/${command}`, true);
    xhr.send(null);
  }
}

  // Add event listeners to the document to listen for key presses
  document.addEventListener('keydown', event => {
    // Check which key was pressed and send the corresponding command
    switch (event.key) {
      case 'ArrowUp':
        if (last_used_command != "forward"){
          last_used_command = "forward";
          sendCommand('forward');
        }
        break;
      case 'ArrowLeft':
        if (last_used_command != "left"){
          last_used_command = "left";
          sendCommand('left');
        }
        break;
      case 'ArrowRight':
        if (last_used_command != "right"){
          last_used_command = "right";
          sendCommand('right');
        }
        break;
      case 'ArrowDown':
        if (last_used_command != "reverse"){
          last_used_command = "reverse";
          sendCommand('reverse');
        }
  
        break;
      default:
        break;
    }
  });

  document.addEventListener('keyup', (event) => {
    last_used_command = "stop";
    sendCommand('stop');
  });
