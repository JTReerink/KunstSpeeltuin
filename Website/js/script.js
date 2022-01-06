function openNav() {
    document.getElementById("navbar").style.display = "block";
}

function closeNav() {
    if(screen.width < 900) {
        document.getElementById("navbar").style.display = "none";
    }
}