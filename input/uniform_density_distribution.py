import numpy
from matplotlib import pyplot 
from amuse.lab import *
from amuse.plot import sph_particles_plot, native_plot
from amuse.ext.evrard_test import uniform_unit_sphere

def plummer_model(N, M, R):
    converter = nbody_system.nbody_to_si(M, R)
    parts = new_plummer_gas_model(N, convert_nbody=converter)
    sph=Fi(converter)
    sph.gas_particles.add_particle(parts)
    sph.evolve_model(1|units.day)
    ch = sph.gas_particles.new_channel_to(parts)
    ch.copy()
    sph.stop()
    return parts

def plot_model(model):
    x_label = "x"
    y_label = "y"
    pyplot.xlabel(x_label)
    pyplot.ylabel(y_label)
    pyplot.scatter(model.x.value_in(nbody_system.length), model.y.value_in(nbody_system.length))
    pyplot.show()


def main(N, Q, Mmin):

    x, y, z = uniform_unit_sphere(N).make_xyz()
    vx, vy, vz = uniform_unit_sphere(N).make_xyz()
    p=Particles(N)
    L = 1 | nbody_system.length
    p.x=L*x
    p.y=L*y
    p.z=L*z
    vL = 1 | nbody_system.speed
    p.vx= vL*vx
    p.vy= vL*vy
    p.vz= vL*vz
    Mmax = 100 | nbody_system.mass
    masses = new_salpeter_mass_distribution(len(p), Mmin, Mmax)
    p.mass = masses
    p.scale_to_standard(virial_ratio=Q)
    #plot_model(p)
    ph = ph4()
    ph.particles.add_particles(p)
    Ekin = ph.kinetic_energy
    Epot = ph.potential_energy
    #print "Energies:", Ekin, Epot, Ekin/Epot
    #print "Masses:", p.mass.sum()
    ph.stop()
    
    for pi in p:
        print pi.mass.value_in(nbody_system.mass), pi.x.value_in(nbody_system.length), pi.y.value_in(nbody_system.length), pi.z.value_in(nbody_system.length), pi.vx.value_in(nbody_system.speed), pi.vy.value_in(nbody_system.speed), pi.vz.value_in(nbody_system.speed)  
        

def new_option_parser():
    from amuse.units.optparse import OptionParser
    result = OptionParser()
    result.add_option("-N", dest="N", type="int",default = 1000,
                      help="number of stars [1000]")
    result.add_option("-Q", dest="Q", type="float",default = 0.13,
                      help="initial virial ratio [%default]")
    result.add_option("-m", dest="Mmin", unit=nbody_system.mass,
                      type="float",default = 0.3 | nbody_system.mass,
                      help="initial virial ratio [%default]")

    return result
if __name__ in ("__main__","__plot__"):
    o, arguments  = new_option_parser().parse_args()
    main(**o.__dict__)






