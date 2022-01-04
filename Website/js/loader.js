const click = document.getElementById("load");
// const button = document.getElementById("load");
const loading = document.getElementById("loading");
const tienTal = document.getElementById("tienTal");
const eenHeid = document.getElementById("eenHeid");

click.addEventListener("click", function() {
    console.log("click");
    loading.style.visibility = "visible";
    tienTal.style.transform = "translateY(-575px)";
    eenHeid.style.transform = "translateY(-1207px)";
    draw();
},false);

tienTal.addEventListener('transitionend', () => {
    console.log("next page");
    window.location.href = './home';
});


let j = 1.00;
let s = 10;
const width = window.innerWidth;
const height = window.innerHeight;


function draw() {
    var canvas = document.getElementById('circle');
        var ctx = canvas.getContext('2d'); 
        var X = canvas.width / 2;
        var Y = canvas.height / 2;
        var R = 97;

        
        
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
            ctx.strokeStyle = 'rgb(169,169,169)';
            ctx.stroke();
            j++;
            if(s<100) {
                s++;
            }
            if (j<101) {
                draw();
                console.log(j)
            }
        }, 400/(s/4)) 
        
}