PID Controller
==============
This module is responsible for implementing a controller algorithm known as PID,
which stands for proportional-integral-derivative controller.

How does it work ?
==================
According to Wikipedia :
> The PID controller calculation algorithm involves three separate constant
> parameters, and is accordingly sometimes called three-term control: the
> proportional, the integral and derivative values, denoted P, I, and D. Simply
> put, these values can be interpreted in terms of time: P depends on the present
> error, I on the accumulation of past errors, and D is a prediction of future
> errors, based on current rate of change.[1] The weighted sum of these three
> actions is used to adjust the process via a control element such as the position
> of a control valve, a damper, or the power supplied to a heating element.

The architecture for an example implementation can be seen below :

![Architecture of the PID](https://raw.github.com/antoinealb/modules/master/modules/pid/pid.png)

This particular implementation is known as a *parallel* (also called ideal)
form. The other common form is called *standard* form. I don't really know which
one is the best honestly.

How is it implemented ?
=======================
For speed reasons, all the filters only work on 32 bit integers, and the PID is
no exception. To allow for finer parameter tuning, the output is shifted to the
right before being sent further down the pipeline. This allows better precision,
while still keeping integer arithmetcs. This modification can be seen below.

![Implementation of the PID](https://raw.github.com/antoinealb/modules/master/modules/pid/pid_implementation.png)

Before being outputed, the value is also
clamped to a maximum, which can be useful if you are feeding it into a PWM
driver which operates on less than 32 bits for example.

How to use it ?
===============
If you have not read it before, you should read the README of 
`modules/control_system_manager`, because it explains a lot of fundamentals
about how control systems are implemented in the code. It also provides an
example control system which uses the PID module as a correct filter. It should
be a good starting point for anyone willing to add a PID filter to their design.

So, the PID controller is intended to be used as a *correct* filter. It can be
used for other filters too, but it would not be very useful, except maybe as a
derivator or an integrator.
