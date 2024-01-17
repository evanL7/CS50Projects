
document.addEventListener('DOMContentLoaded', function() {

    document.querySelector('#button_darkmode').onclick = function() {
        var element = document.body;
        element.classList.toggle("dark-mode");

        let not_current_mode = document.querySelector('#button_darkmode').innerHTML;
        if (not_current_mode == 'Darkmode') {
            document.querySelector('#button_darkmode').innerHTML = 'Lightmode';
        }
        else
        {
            document.querySelector('#button_darkmode').innerHTML = 'Darkmode';
        }

    }

});