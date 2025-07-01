import numpy as np

from typing import Callable, Union, List

def GL(
    alpha: float,
    f: Union[Callable, np.ndarray, List[float, int]],
    domain_start: float = 0.0,
    domain_end: float = 1.0,
    num_points: int = 100,
) -> np.ndarray:
    """ Computes the GL fractional derivative of a function for an entire array
        of function values.

        Parameters
       ==========
        alpha : float
            The order of the differintegral to be computed.
        f_name : function handle, lambda function, list, or 1d-array of
                 function values
            This is the function that is to be differintegrated.
        domain_start : float
            The left-endpoint of the function domain. Default value is 0.
        domain_end : float
            The right-endpoint of the function domain; the point at which the
            differintegral is being evaluated. Default value is 1.
        num_points : integer
            The number of points in the domain. Default value is 100.

        Examples:
        >>> DF_poly = GL(-0.5, lambda x: x**2 - 1)
        >>> DF_sqrt = GL(0.5, lambda x: np.sqrt(x), 0., 1., 100)
    """
    ...

def GLpoint(
    alpha: float,
    f: Union[Callable, np.ndarray, List[float, int]],
    domain_start: float = 0.0,
    domain_end: float = 1.0,
    num_points: int = 100,
) -> float:
    """Computes the GL fractional derivative of a function at a point.

    Parameters
    ==========
     alpha : float
         The order of the differintegral to be computed.
     f_name : function handle, lambda function, list, or 1d-array of
              function values
         This is the function that is to be differintegrated.
     domain_start : float
         The left-endpoint of the function domain. Default value is 0.
     domain_end : float
         The right-endpoint of the function domain; the point at which the
         differintegral is being evaluated. Default value is 1.
     num_points : integer
         The number of points in the domain. Default value is 100.

     Examples:
     >>> DF_poly = GLpoint(-0.5, lambda x: 3*x**2 - 9*x + 2)
     >>> DF_sqrt = GLpoint(0.5, lambda x: np.sqrt(x), 0., 1., 100)
    """
    ...

def RL(
    alpha: float,
    f: Union[Callable, np.ndarray, List[float, int]],
    domain_start: float = 0.0,
    domain_end: float = 1.0,
    num_points: int = 100,
) -> np.ndarray:
    """ Calculate the RL algorithm using a trapezoid rule over
        an array of function values.

    Parameters
    ==========
        alpha : float
            The order of the differintegral to be computed.
        f_name : function handle, lambda function, list, or 1d-array of
                 function values
            This is the function that is to be differintegrated.
        domain_start : float
            The left-endpoint of the function domain. Default value is 0.
        domain_end : float
            The right-endpoint of the function domain; the point at which the
            differintegral is being evaluated. Default value is 1.
        num_points : integer
            The number of points in the domain. Default value is 100.

    Output
    ======
        RL : float 1d-array
            Each element of the array is the RL differintegral evaluated at the
            corresponding function array index.

    Examples:
        >>> RL_sqrt = RL(0.5, lambda x: np.sqrt(x))
        >>> RL_poly = RL(0.5, lambda x: x**2 - 1, 0., 1., 100)
    """
    ...


def RLpoint(
    alpha: float,
    f: Union[Callable, np.ndarray, List[float, int]],
    domain_start: float = 0.0,
    domain_end: float = 1.0,
    num_points: int = 100,
) -> float:
    """Calculate the RL differintegral at a point with the trapezoid rule.

    Parameters
       ==========
        alpha : float
            The order of the differintegral to be computed.
        f_name : function handle, lambda function, list, or 1d-array of
                 function values
            This is the function that is to be differintegrated.
        domain_start : float
            The left-endpoint of the function domain. Default value is 0.
        domain_end : float
            The right-endpoint of the function domain; the point at which the
            differintegral is being evaluated. Default value is 1.
        num_points : integer
            The number of points in the domain. Default value is 100.

        Examples:
        >>> RL_sqrt = RLpoint(0.5, lambda x: np.sqrt(x))
        >>> RL_poly = RLpoint(0.5, lambda x: x**2 - 4*x - 1, 0., 1., 100)
    """
    ...