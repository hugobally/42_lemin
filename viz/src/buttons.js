var rangeSlider = document.getElementById('slider-range-speed');

minTurnSpeed = bigMap ? 5000 : 1000;
maxTurnSpeed = bigMap ? 500 : 0;

noUiSlider.create(rangeSlider, {
    start: [turnDuration],
    direction: 'rtl',
    range: {
        'min': [maxTurnSpeed],
        'max': [minTurnSpeed]
    }
});

rangeSlider.noUiSlider.on('change', () => {
    turnDuration = parseInt(rangeSlider.noUiSlider.get())
});

function launchTurnsButton() {
    if (!preventOtherEvents)
        runTurns();
}