import pytest
import numpy as np
from geometry import SO3
RSEED = 144440

class TestSO3:
    def test_action(self):
        np.random.seed(RSEED)
        q = SO3.random()
        v = np.random.random(3)
        qv1 = q * v
        qv2 = q.R().dot(v)
        assert np.allclose(qv1, qv2)

    def test_inversion_and_composition(self):
        np.random.seed(RSEED)
        qI = SO3.identity()
        q1 = SO3.random()
        q1i = q1.inverse()
        q1I = q1 * q1i
        assert np.allclose(qI.array(), q1I.array())

    def test_euler_convs(self):
        roll = -1.2
        pitch = 0.6
        yaw = -0.4
        q = SO3.fromEuler(roll, pitch, yaw)
        rpy = q.toEuler()
        assert np.isclose(roll, rpy[0]) and np.isclose(pitch, rpy[1]) and np.isclose(yaw, rpy[2])
    
    def test_plus_minus(self):
        np.random.seed(RSEED)
        R1 = SO3.random()
        w = np.array([0.5, 0.2, 0.1])
        R2 = R1 + w
        w2 = R2 - R1
        assert np.allclose(w, w2)

    def test_chart_maps(self):
        np.random.seed(RSEED)
        q = SO3.random()
        w = np.random.random(3)
        qlog = SO3.Log(q)
        q2 = SO3.Exp(qlog)
        assert np.allclose(q.array(), q2.array())
        wexp = SO3.Exp(w)
        w2 = SO3.Log(wexp)
        assert np.allclose(w, w2)

    def test_constructors(self):
        q_vec = np.array([1, 0, 0, 0])
        q = SO3(q_vec)
        assert(q.w() == 1)
        assert(q.x() == 0)
        assert(q.y() == 0)
        assert(q.z() == 0)

    def test_mutable_array(self):
        q = SO3.identity()
        q_arr = q.array()
        q_arr[0] = 2
        assert q_arr[0] == 2
        assert q.w() == 1

    def test_scaling(self):
        np.random.seed(RSEED)
        qI = SO3.identity()
        qIs = 5.0 * qI
        assert np.allclose(qI.array(), qIs.array())
        qr = SO3.random()
        qr2 = qr * 0.2
        qr3 = qr2 / 0.2
        assert np.allclose(qr.array(), qr3.array())
