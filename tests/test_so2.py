import pytest
import numpy as np
from geometry import SO2
RSEED = 144440

class TestSO2:
    def test_action(self):
        np.random.seed(RSEED)
        q = SO2.random()
        v = np.random.random(2)
        qv1 = q * v
        qv2 = q.R().dot(v)
        assert np.allclose(qv1, qv2)

    def test_inversion_and_composition(self):
        np.random.seed(RSEED)
        qI = SO2.identity()
        q1 = SO2.random()
        q1i = q1.inverse()
        q1I = q1 * q1i
        assert np.allclose(qI.array(), q1I.array())

    def test_angle_convs(self):
        angle = -0.4
        q = SO2.fromAngle(angle)
        angle2 = q.angle()
        assert np.isclose(angle, angle2)
    
    def test_plus_minus(self):
        np.random.seed(RSEED)
        R1 = SO2.random()
        w = np.array([0.5])
        R2 = R1 + w
        w2 = R2 - R1
        assert np.allclose(w, w2)

    def test_chart_maps(self):
        np.random.seed(RSEED)
        q = SO2.random()
        w = np.random.random(2)
        qlog = SO2.Log(q)
        q2 = SO2.Exp(qlog)
        assert np.allclose(q.array(), q2.array())
        wexp = SO2.Exp(w)
        w2 = SO2.Log(wexp)
        assert np.allclose(w, w2)

    def test_constructors(self):
        q_vec = np.array([1, 0])
        q = SO2(q_vec)
        assert(q.w() == 1)
        assert(q.x() == 0)

    def test_mutable_array(self):
        q = SO2.identity()
        q_arr = q.array()
        q_arr[0] = 2
        assert q_arr[0] == 2
        assert q.w() == 1

    def test_scaling(self):
        np.random.seed(RSEED)
        qI = SO2.identity()
        qIs = 5.0 * qI
        assert np.allclose(qI.array(), qIs.array())
        qr = SO2.random()
        qr2 = qr * 0.2
        qr3 = qr2 / 0.2
        assert np.allclose(qr.array(), qr3.array())
