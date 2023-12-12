from math import *

# 1) Measurment Update Step
def update(mean1, var1, mean2, var2):
    new_mean = ( var1*mean2 + var2*mean1) / (var1 + var2)
    new_var = 1 / ( (1/var1) + (1/var2) )
    return [new_mean, new_var]



# 2) Motion Update Step
'''
M' = M + u
v' = v^2 + r^2
where :                                 where:
M' : Motion updated mean                v' : updated covariance
M : Prior mean                          v^2 : Prior covariance
u : motion mean                         r^2 : motion covariance
'''
def predict(mean1, var1, mean2, var2):
    new_mean = mean1 + mean2
    new_var = var1 + var2
    return [new_mean, new_var]



# KF code
measurements = [5., 6., 7., 9., 10.]
motion = [1., 1., 2., 1., 1.]
measurement_sig = 4.
motion_sig = 2.
mu = 0.
sig = 10000.


for n in range(len(measurements)):
    [mu,sig] = update(mu,sig,measurements[n],measurement_sig)
    print('update : ',[mu, sig])
    [mu,sig] = predict(mu,sig,motion[n],motion_sig)
    print('predict : ',[mu, sig])
