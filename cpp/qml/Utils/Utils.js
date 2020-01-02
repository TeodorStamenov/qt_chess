

function formatTime (value)
{
    var seconds = value % 60;
    var minutes = Math.floor(Math.floor((value / 60)) % 60);
    var hours   = Math.floor(Math.floor(value / 60) / 60);

    var hoursStr   = hours.toString();
    var minutesStr = minutes.toString();
    var secondsStr = seconds.toString();

    return "%1:%2:%3"
                    .arg(hoursStr.padStart(2, '0'))
                    .arg(minutesStr.padStart(2, '0'))
                    .arg(secondsStr.padStart(2, '0'));
}
