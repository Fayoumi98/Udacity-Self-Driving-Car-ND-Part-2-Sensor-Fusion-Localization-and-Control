p = [0.2, 0.2, 0.2, 0.2, 0.2]
world = ['green', 'red', 'red', 'green', 'green']
motions = [1,1]
measurements = ['red', 'green']

pHit = 0.6
pMiss = 0.2

pExact = 0.8
pOvershoot = 0.1
pUndershoot = 0.1




def sense(p, Z):

    q=[]
    
    for i in range(len(p)):

        hit = (Z == world[i])
        q.append(p[i] * (hit * pHit + (1-hit) * pMiss))

    s = sum(q)

    for i in range(len(q)):

        q[i] = q[i] / s
    
    return q




def move(p, U):

    q = []
    
    for i in range(len(p)):

        s = pExact * p[(i-U) % len(p)]
        s = s + pOvershoot * p[(i-U-1) % len(p)]
        s = s + pUndershoot * p[(i-U+1) % len(p)]
        
        q.append(s)

    return q


# Move twice
'''
for k in range(2):
    p = move(p,1)
'''

# Move 1000
'''
for k in range(1000):
    p = move(p,1)
'''

# Sense and Move
# [0.21157894736842103, 0.1515789473684211, 0.08105263157894739, 0.16842105263157897, 0.3873684210526316]
# the cell of the highest probability is the predicted cell 0.3873684210526316
# red => green => green (predicted)
'''
for k in range(len(measurements)):
    p = sense(p,measurements[k])
    p = move(p,motions[k])

'''

for k in range(len(measurements)):
    p = sense(p,measurements[k])
    p = move(p,motions[k])

print(p)