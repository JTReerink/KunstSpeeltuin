const click = document.getElementById("load");
// const button = document.getElementById("load");
const loading = document.getElementById("loading");
const tienTal = document.getElementById("tienTal");
const eenHeid = document.getElementById("eenHeid");

click.addEventListener("click", function() {
    loading.style.visibility = "visible";
    tienTal.style.transform = "translateY(-572px)";
    eenHeid.style.transform = "translateY(-1204px)";
    draw();
},false);

tienTal.addEventListener('transitionend', () => {
    console.log("next page");
    window.location.href = './home';
});


let j = 1.00;
let s = 10.000;
var R = 85;
var canvas = document.getElementById('circle');
var ctx = canvas.getContext('2d'); 
var X = canvas.width / 2;
var Y = canvas.height / 2;
const width = window.innerWidth;
const height = window.innerHeight;


function draw() {
    setTimeout(function () {
        
        ctx.clearRect(0,0,width,height)
        ctx.beginPath();
        ctx.arc(X, Y, R, 0, 2 * Math.PI, false);
        ctx.lineWidth = 3;
        ctx.strokeStyle = 'rgb(169,169,169,0.5)';
        ctx.stroke();
        ctx.beginPath();
        ctx.arc(X, Y, R, 0 - (0.5*Math.PI), (Math.PI * (2/100*j)) - (0.5*Math.PI), false);
        ctx.lineWidth = 3;
        ctx.strokeStyle = 'white';
        ctx.stroke();
        j++;
        R += 0.020 + (s/500);
        if(s<100) {
            s++;
        }
        if (j<101) {
            draw();
        }
    }, 400/(s/4));     
}