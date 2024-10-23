def __init__(self,X,Y,Z):
    self.x = X & Y | Z 
    self.y = Y & Z | X
    self.z = Z & X | Y