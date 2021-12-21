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
},false);

tienTal.addEventListener('transitionend', () => {
    console.log("next page");
    window.location.href = './home';
})