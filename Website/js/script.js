function openNav() {
    document.getElementById("navbar").style.display = "block";
}

function closeNav() {
    if(screen.width < 900) {
        document.getElementById("navbar").style.display = "none";
    }
}



// function checkColorChange() {
//     setTimeout(function () {
//         let mydata = JSON.parse(data);
//         console.log(mydata[1]);
//         checkColorChange();
//     }, 2000);
// }

// checkColorChange();
fetch("http://schw.hosts1.ma-cloud.nl/jaap/control.json")
  .then(response => response.json())
  .then(json => console.log(json));