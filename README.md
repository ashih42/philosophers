# philosophers
My solution for the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in C using [SDL2](https://www.libsdl.org/download-2.0.php). (42 Silicon Valley)

<p float="left">
  <img src="https://github.com/ashih42/philo/blob/master/Screenshots/philo.png" width="540" />
</p>

* All even-numbered philosophers will eat, sleep, think, sleep, ...
* All odd-numbered philosophers will think, sleep, eat, sleep, ...

## Prerequisites

You are on macOS with `gcc`, `make`, and `brew` installed.

## Installing

```
./setup.sh
```

## Running

Start simulation with `n` philosophers.  If unspecified, 7 philosophers are set by default.

```
./philo n
```

## Controls

* `H` Toggle health number/bar.
* `Escape` Terminate the simulation.
