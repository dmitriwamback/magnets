# Magnet Simulator

Top-down 2D magnet simulator in OpenGL using electromagnetic physics.

## How to run


## Theory

### Softened distance

<p></p>

The dipole field blows up as the distance converges to zero. To keep the distance finite, a small $ϵ$ is used to reduce the possibilty of dividing by zero:

$$ d^2 = \lVert \vec{r} \lVert ^2 + ϵ^2, \qquad \hat{r} = \frac{\vec{r}}{d} $$

<p></p>

Where:

1. $\vec{r}$ is the separation between two magnets

### Magnetic field on a single dipole

A magnet with moment $\vec{m}$ creates, at separation $\vec{r}$ from itself, the field is defined:

<p></p>

$$ B(\vec{r}) = k\frac{3(\vec{m} \cdot \hat{r})\hat{r} - \vec{m}}{d^3} $$

<p></p>

This produces a field-line pattern such that field lines leave the north pole and loop around to the south pole. The $\frac{1}{d^3}$ parameter indicates the field is strong nearby and falls off quickly with distance.

<p></p>

### Smooth cutoff taper

Farther magnets contribute very little. As a technical optimization, only magnets within a certain radius $R$ are considered. However, cutting them off abruptly would cause small force jumps (visible as jitter). So each contribution is multiplied by a smooth weight:

$$ s = clamp(\frac{\lVert \vec{r} \lVert - 0.8R}{0.2R}, 0, 1) \qquad w(\vec{r}) = 1 - s^2(3 - 2s) $$

<p></p>

$w = 1$ when the magnet is within the $0.8R$ and gradually converges to $0$ when the magnet is between $0.8R$ and $R$. We apply this $w$ for every field at their current position.

<p></p>

Additionally, to reduce the number of checks, we implement a quadtree to only iterate nearby magnets and neglect farther away magnets.

### Total field at a magnet

The field at magnet $i$ can be represented as the sum of its neighbors assuming theyre in the radius $R$ and what the quadtree returns:

$$ \vec{B_i} = \sum_{j \in nearby} w(\vec{r_{ij}})\vec{B}(\vec{r}_{ij}) $$

A magnet however can never contribute to its own field so we must check such that $i \neq j$; its self-field is singular at its center and a magnet cannot push on itself.

### Energy, force and torque

A dipole in an external field has potential energy described as the dot product between the moment and the field:

$$ U = -\vec{m} \cdot \vec{B} $$

Low energy means that the moment is aligned with the field. Forces and torque are the negative derivatives of this energy. The force is the derivative with respect to $x$ and torque with respect to the angle.

<p></p>

The force can be represented as the gradient of this energy:

$$ \vec{F} = -\vec{∇}U = \vec{∇}(\vec{m} \cdot \vec{B}) = (\vec{m} \cdot \vec{∇})\vec{B} $$

We can similarly represent the force in vector form:

$$ \vec{F} = (\vec{m}_x \frac{\partial \vec{B_x}}{\partial x} + \vec{m}_y \frac{\partial \vec{B_y}}{\partial x}, \
   \vec{m}_x \frac{\partial \vec{B_x}}{\partial y} + \vec{m}_y \frac{\partial \vec{B_y}}{\partial y}) $$

The derivatives can be computed numerically by central differences with a small step $h$ (about 1% of the magnet size):

$$ \frac{\partial \vec{B}}{\partial x} = \frac{\vec{B}(x + h, y) - \vec{B}(x - h, y)}{2h} $$

and:

$$ \frac{\partial \vec{B}}{\partial y} = \frac{\vec{B}(x, y + h) - \vec{B}(x, y - h)}{2h} $$

Differentiating the dipole field gives an exact expression for the force between two magnets with $\vec{r}$ pointing from $j$ to $i$:

$$ \vec{F}_{ij} = \frac{3kw}{d^4}[(\vec{m}_j \cdot \hat{r})\vec{m}_i + (\vec{m}_i \cdot \hat{r})\vec{m}_j + (\vec{m}_i \cdot \vec{m}_j)\hat{r} - 5(\vec{m}_j \cdot \hat{r})(\vec{m}_i \cdot \hat{r})\hat{r}] $$

$$ \vec{F}_{ji} = -\vec{F}_{ij} $$

As we calculated force, it is now time to move with torque. Torque can be defined as:

$$ \tau = -\frac{\partial U}{\partial \theta} = (\vec{m} \times \vec{B})_z = \vec{m}_x\vec{B}_y - \vec{m}_y\vec{B}_x $$

Evaluated with $\vec{B} = \vec{B}_i$. The magnet rotates until its moment lines up with the local field.

### Contact

The point-dipole force diverges at touching distance, so each magnet also gets a physical body. For radii $a_i, \ a_j$ and separation $r < a_i + a_j$:

$$ \delta = (a_i + a_j) - r, \qquad \vec{F}_{contact} = \kappa \delta \hat{r}_{ij} - c_n(\vec{v}_{rel} \cdot \hat{r})\hat{r} $$

The first term pushes overlapping magnets apart, and the second damps their approach spped so they do not bounce indefinitely.

<p></p>

We use the semi-implicit Euler implementation to move and rotate the objects with our given force and torque:

<p></p>

$$ \vec{v} \leftarrow \vec{v} + \frac{\vec{F}}{M}Δt, \qquad \vec{v} \leftarrow \vec{v}(1 - c_{lin}Δt), \qquad \vec{x} \leftarrow \vec{x} + \vec{v}Δt $$

<p></p>

$$ \omega \leftarrow \omega + \frac{\tau}{I}Δt, \qquad \omega \leftarrow \omega(1 - c_{ang}Δt), \qquad \theta \leftarrow \theta + \omega Δt $$

<p></p>

As the magnet rotates, we must take into account the dipole's rotation as well. This can be modelled as:

$$ \vec{m} = \lVert \vec{m} \lVert (\cos(\theta + \phi), \sin(\theta + \phi)) $$

Where:
1. $\theta$ is the rotation of the magnet.
2. $\phi$ is the initial rotation of the dipole.

### Alternative Model (Two-pole bar magnet)

