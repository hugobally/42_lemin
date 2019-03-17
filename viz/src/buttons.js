var rangeSlider = document.getElementById('slider-range-speed');

noUiSlider.create(rangeSlider, {
    start: [turnDuration],
    direction: 'rtl',
    range: {
        'min': [100],
        'max': [3000]
    }
});

rangeSlider.noUiSlider.on('change', () => {
    turnDuration = parseInt(rangeSlider.noUiSlider.get())
});