# Magnet Simulator

Top-down 2D magnet simulator in OpenGL using electromagnetic physics.

## How to run


## Theory

### Softened distance

<p></p>

The dipole field blows up as the distance converges to zero. To keep the distance finite, a small $\epsilon$ is used to reduce the possibility of dividing by zero:

$$ d^2 = \lVert \vec{r} \rVert ^2 + \epsilon^2, \qquad \hat{r} = \frac{\vec{r}}{d} $$

<p></p>

Where:

1. $\vec{r}$ is the separation between two magnets

### Magnetic field of a single dipole

A magnet with moment $\vec{m}$ creates, at separation $\vec{r}$ from itself, the field defined as:

<p></p>

$$ \vec{B}(\vec{r}) = k\frac{3(\vec{m} \cdot \hat{r})\hat{r} - \vec{m}}{d^3} $$

<p></p>

Where:

1. $k$ is a strength constant (stands in for $\frac{\mu_0}{4\pi}$)
2. $\vec{m}$ is the magnetic moment of the magnet

<p></p>

This produces a field-line pattern such that field lines leave the north pole and loop around to the south pole. The $\frac{1}{d^3}$ factor means the field is strong nearby and falls off quickly with distance.

<p></p>

### Smooth cutoff taper

Farther magnets contribute very little. As a technical optimization, only magnets within a certain radius $R$ are considered. However, cutting them off abruptly would cause small force jumps (visible as jitter). So each contribution is multiplied by a smooth weight:

$$ s = clamp\left(\frac{\lVert \vec{r} \rVert - 0.8R}{0.2R}, 0, 1\right) \qquad w(\vec{r}) = 1 - s^2(3 - 2s) $$

<p></p>

$w = 1$ when the magnet is within $0.8R$ and gradually converges to $0$ between $0.8R$ and $R$, reaching $0$ at $R$. We apply this $w$ to every field contribution.

<p></p>

Additionally, to reduce the number of checks, we implement a quadtree to only iterate nearby magnets and neglect farther away magnets.

### Total field at a magnet

The field at magnet $i$ can be represented as the sum of the fields from its neighbors, assuming they're within the radius $R$ and returned by the quadtree:

$$ \vec{B}_i = \sum_{j \in \text{nearby}} w(\vec{r}_{ij})\vec{B}_j(\vec{r}_{ij}) $$

<p></p>

Where:

1. $\vec{B}_j$ is the field created by magnet $j$.
2. $\vec{r}_{ij}$ is the separation from magnet $j$ to magnet $i$.

<p></p>

A magnet however can never contribute to its own field so we must check such that $i \neq j$; its self-field is singular at its center and a magnet cannot push on itself.

### Energy, force and torque

A dipole in an external field has potential energy described as the dot product between the moment and the field:

$$ U = -\vec{m} \cdot \vec{B} $$

Low energy means that the moment is aligned with the field. Forces and torque are the negative derivatives of this energy. The force is the derivative with respect to position and torque is the derivative with respect to the angle.

<p></p>

The force can be represented as the gradient of this energy:

$$ \vec{F} = -\nabla U = \nabla(\vec{m} \cdot \vec{B}) = (\vec{m} \cdot \nabla)\vec{B} $$

The last step works because the curl of $\vec{B}$ is zero where there are no currents.

<p></p>

We can similarly represent the force in component form:

$$ \vec{F} = \left(m_x \frac{\partial B_x}{\partial x} + m_y \frac{\partial B_y}{\partial x}, \quad m_x \frac{\partial B_x}{\partial y} + m_y \frac{\partial B_y}{\partial y}\right) $$

The derivatives can be computed numerically by central differences with a small step $h$ (about 1% of the magnet size):

$$ \frac{\partial \vec{B}}{\partial x} \approx \frac{\vec{B}(x + h, y) - \vec{B}(x - h, y)}{2h} $$

and:

$$ \frac{\partial \vec{B}}{\partial y} \approx \frac{\vec{B}(x, y + h) - \vec{B}(x, y - h)}{2h} $$

Differentiating the dipole field gives an exact expression for the force between two magnets with $\vec{r}$ pointing from $j$ to $i$:

$$ \vec{F}_{ij} = \frac{3kw}{d^4}[(\vec{m}_j \cdot \hat{r})\vec{m}_i + (\vec{m}_i \cdot \hat{r})\vec{m}_j + (\vec{m}_i \cdot \vec{m}_j)\hat{r} - 5(\vec{m}_j \cdot \hat{r})(\vec{m}_i \cdot \hat{r})\hat{r}] $$

$$ \vec{F}_{ji} = -\vec{F}_{ij} $$

Using the same energy, we can move onto torque, differentiating it with respect to $\theta$. Torque can be defined as:

$$ \tau = -\frac{\partial U}{\partial \theta} = (\vec{m} \times \vec{B})_z = m_x B_y - m_y B_x $$

Evaluated with $\vec{B} = \vec{B}_i$. The magnet rotates until its moment lines up with the local field.

### Contact

The point-dipole force diverges at touching distance, so each magnet also gets a physical body. For radii $a_i, \ a_j$ and separation $r < a_i + a_j$:

$$ \delta = (a_i + a_j) - r, \qquad \vec{F}_{contact} = \kappa \delta \hat{r}_{ij} - c_n(\vec{v}_{rel} \cdot \hat{r}_{ij})\hat{r}_{ij} $$

<p></p>

Where:

1. $\kappa$ is the contact stiffness
2. $c_n$ is the contact damping coefficient
3. $\vec{v}_{rel} = \vec{v}_i - \vec{v}_j$ is the relative velocity of the two magnets

<p></p>

The first term pushes overlapping magnets apart, and the second damps their approach speed so they do not bounce indefinitely.

### Integration

We use the semi-implicit Euler implementation to move and rotate the objects with our given force and torque:

<p></p>

$$ \vec{v} \leftarrow \vec{v} + \frac{\vec{F}}{M}\Delta t, \qquad \vec{v} \leftarrow \vec{v}(1 - c_{lin}\Delta t), \qquad \vec{x} \leftarrow \vec{x} + \vec{v}\Delta t $$

<p></p>

$$ \omega \leftarrow \omega + \frac{\tau}{I}\Delta t, \qquad \omega \leftarrow \omega(1 - c_{ang}\Delta t), \qquad \theta \leftarrow \theta + \omega \Delta t $$

<p></p>

Where:

1. $M$ is the mass of the magnet
2. $I$ is the moment of inertia of the magnet
3. $c_{lin}$ and $c_{ang}$ are the linear and angular drag coefficients

### Dipole rotation

As the magnet rotates, we must take into account the dipole's rotation as well. The moment is recomputed from the new angle every step. This can be modelled as:

$$ \vec{m} = \lVert \vec{m} \rVert (\cos(\theta + \phi), \sin(\theta + \phi)) $$

Where:
1. $\theta$ is the rotation of the magnet.
2. $\phi$ is the fixed rotation offset of the dipole relative to the magnet, set once when the magnet is created.

### Alternative Model (Two-pole bar magnet)

In the first model, the dipole is only accurate from far away. Up close, it neglects the length of the magnet, so bars cannot snap side by side or pivot around each other. To fix this, the magnet is modelled as two magnetic poles of opposite charge $+q$ and $-q$ placed at opposite ends.

<p></p>

The pole positions follow the body as it rotates, using the same formula for the rotation as the dipoles:

$$ \hat{u} = (\cos(\theta + \phi), \sin(\theta + \phi)), \qquad \vec{p}_{\pm} = \vec{x} \pm \frac{L}{2}\hat{u} $$

<p></p>

Where:

1. $\vec{x}$ is the center of the magnet
2. $L$ is the distance between the two poles.
3. $\vec{p}_+$ is the north pole and $\vec{p}_-$ is the south pole.

<p></p>

The pole strength is related to the moment from the dipole model, so both models describe the same magnet:

$$ q = \frac{\lVert \vec{m} \lVert}{L}$$

### Forces between poles

Poles exhibit the same physics as electric charges. For poles $a$ and $b$ with $\vec{r}_{ab}$ pointing from $b$ to $a$:

$$ \vec{F}_{ab} = \left(k_p \frac{q_a q_b}{d^2}\hat{r}_{ab}\right)w(\vec{r}_{ab}), \qquad \vec{F}_{ba} = -\vec{F}_{ab} $$

Where:

1. $k_p$ is the pole strength constant.
2. $d$ and $\hat{r}_{ab}$ are the softened distance and direction from before.
3. $w(\vec{r}_{ab})$ is the same smooth cutoff taper.

<p></p>

