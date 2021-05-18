# L-system-Laboratory

This application was created as part of my final year project at The University of Sheffield. The application was designed to allow a user to model a parametric L-system with a focus on modelling branching structures.

## Application

The application is simple in design and use. Simply enter your desired L-system parameters in the corresponding fields to the right of the window and select the "generate" button to display the L-system in 3D. Should you require any help the instructions button contains details of how format your L-system.

![L-system-Laboratory Application](https://github.com/AidenJefferson/L-system-Laboratory/blob/main/images/application.png)


## Installation

To install L-system Laboratory you can use the [installer](https://github.com/AidenJefferson/L-system-Laboratory/blob/main/Installer/L-system-Laboratory.exe) provided above. However, should you wish to install the application using source code you will require the [Qt Creator IDE](https://www.qt.io/product/development-tools).

## Example L-systems

The following are some examples of the types of L-systems capable of being produced by the application.

### Vine Structure 

    ![Vine L-system](https://github.com/AidenJefferson/L-system-Laboratory/blob/main/images/vine.png "Vine L-system")

```
    
    n = 5
    
    #define a 22.5      /* Branching Angle */
    #define d 1         /* Drawing Distance */
    
    w : !(0.08)F(d)-(a)F(d)+(a)F(d)-(a)F(d)+(a)
    p1: F(l): → F(l)+(a)F(l)-(a)[F(l/2)F(l/2)+(a)F(l/2)][F(l/2)-(a)F(l/2)]
    p2: -(a): → +(a)
    p3: +(a): → -(a)
    
```

### Cactus Structure 

    ![Cactus L-system](https://github.com/AidenJefferson/L-system-Laboratory/blob/main/images/cactus.png "Cactus L-system")

```
    
    n = 10
    
    #define a 18        /* Branching Angle */
    
    w : S(1,1)L(1,1)F(1)F(1)F(1)
    p1: S(l,w): → [+(a)+(a)+(a)G(l,w)][-(a)-(a)-(a)G(l,w)]T(l,w)S(l,w)
    p2: G(l,w): → +(a)H(l,w)[-(a)G(l,w)]L(l,w)
    p3: H(l,w): → -(a)G(l,w)[+(a)H(l,w)]L(l,w)
    p4: T(l,w): → T(l,w)L(l,w)
    p5: L(l,w): → [-(a)F(l)F(l)F(l)][+(a)F(l)F(l)F(l)]F(l)
    
```

### Tree Structure 

    ![Tree L-system](https://github.com/AidenJefferson/L-system-Laboratory/blob/main/images/tree.png "Tree L-system")

```
    
    n = 9
    
    #define r 0.9       /* Contraction ratio 1 */
    #define s 0.8       /* Contraction ratio 2 */
    #define a 30        /* Branching angle 1 */
    #define b 25        /* Branching angle 2 */
    #define x 0.707     /* Width decreasing rate */
    
    w : A(10,1)
    p1: A(l,w): → !(w)F(l)[<(b)&(a)B(l*r,w*x)]>(180)[<(a)&(b)B(l*s,w*x)]
    p2: B(l,w): → !(w)F(l)[<(b)+(a)$B(l*r,w*x)][<(a)-(b)$B(l*s,w*x)]
    
```
