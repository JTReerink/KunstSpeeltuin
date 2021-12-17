const button = document.getElementById("load");

button.addEventListener("click", function() {
    console.log("click");
    document.getElementById("tienTal").style.transform = "translateY(-317px)";
    document.getElementById("eenHeid").style.transform = "translateY(-668px)";
},false);