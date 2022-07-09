import pytest
import numpy as np
from geometry import SE2
RSEED = 144440

class TestSE2:
    def test_action(self):
        np.random.seed(RSEED)
        x = SE2.identity()
        v = np.random.random(2)
        xv = x * v
        assert np.allclose(v, xv)

    def test_inversion_and_composition(self):
        np.random.seed(RSEED)
        TI = SE2.identity()
        T1 = SE2.random()
        T1i = T1.inverse()
        T2 = T1 * T1i
        assert np.allclose(TI.array(), T2.array())

    def test_plus_minus(self):
        np.random.seed(RSEED)
        T1 = SE2.random()
        w = np.random.random(6)
        T2 = T1 + w
        w2 = T2 - T1
        assert np.allclose(w, w2)
        
    def test_chart_maps(self):
        np.random.seed(RSEED)
        T = SE2.random()
        w = np.random.random(3)
        t2 = SE2.Log(T)
        T2 = SE2.Exp(t2)
        assert np.allclose(T.array(), T2.array())
        W2 = SE2.Exp(w)
        w2 = SE2.Log(W2)
        assert np.allclose(w, w2)

    def test_constructors(self):
        x_vec = np.array([1, 0, 1, 0])
        x = SE2(x_vec)
        assert(x.t()[0] == 1)
        assert(x.t()[1] == 0)
        assert(x.q().w() == 1)
        assert(x.q().x() == 0)

    def test_mutable_array(self):
        x = SE2.identity()
        x_arr = x.array()
        x_arr[0] = 2
        x.t()[0] = 3
        assert x_arr[0] == 2
        assert x.t()[0] == 3
    
    def test_scaling(self):
        np.random.seed(RSEED)
        qI = SE2.identity()
        qIs = 5.0 * qI
        assert np.allclose(qI.array(), qIs.array())
        qr = SE2.random()
        qr2 = qr * 0.2
        qr3 = qr2 / 0.2
        assert np.allclose(qr.array(), qr3.array())
