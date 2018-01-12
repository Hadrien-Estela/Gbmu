// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//    Defines.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/30 11:20:25 by hestela           #+#    #+#             //
//   Updated: 2015/12/30 11:20:28 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef  DEFINES_HPP
# define  DEFINES_HPP

// return the value of Bit x
# define BIT_0(x) 		(x & 0b0000000000000001)
# define BIT_1(x) 		(x & 0b0000000000000010)
# define BIT_2(x) 		(x & 0b0000000000000100)
# define BIT_3(x) 		(x & 0b0000000000001000)
# define BIT_4(x) 		(x & 0b0000000000010000)
# define BIT_5(x) 		(x & 0b0000000000100000)
# define BIT_6(x) 		(x & 0b0000000001000000)
# define BIT_7(x) 		(x & 0b0000000010000000)
# define BIT_8(x) 		(x & 0b0000000100000000)
# define BIT_9(x) 		(x & 0b0000001000000000)
# define BIT_10(x) 		(x & 0b0000010000000000)
# define BIT_11(x) 		(x & 0b0000100000000000)
# define BIT_12(x) 		(x & 0b0001000000000000)
# define BIT_13(x) 		(x & 0b0010000000000000)
# define BIT_14(x) 		(x & 0b0100000000000000)
# define BIT_15(x) 		(x & 0b1000000000000000)

// return the value of Bits x to y (included)
# define BITS_0_1(x) 	(x & 0b0000000000000011)
# define BITS_0_2(x) 	(x & 0b0000000000000111)
# define BITS_0_3(x) 	(x & 0b0000000000001111)
# define BITS_0_4(x) 	(x & 0b0000000000011111)
# define BITS_0_5(x) 	(x & 0b0000000000111111)
# define BITS_0_6(x) 	(x & 0b0000000001111111)
# define BITS_1_2(x) 	((x & 0b0000000000000110) >> 1)
# define BITS_2_3(x) 	((x & 0b0000000000001100) >> 2)
# define BITS_3_5(x) 	((x & 0b0000000000111000) >> 3)
# define BITS_4_5(x) 	((x & 0b0000000000110000) >> 4)
# define BITS_4_6(x) 	((x & 0b0000000001110000) >> 4)
# define BITS_4_7(x) 	((x & 0b0000000011110000) >> 4)
# define BITS_5_6(x) 	((x & 0b0000000001100000) >> 5)
# define BITS_5_9(x) 	((x & 0b0000001111100000) >> 5)
# define BITS_6_7(x) 	((x & 0b0000000011000000) >> 6)
# define BITS_8_9(x) 	((x & 0b0000001100000000) >> 8)
# define BITS_10_11(x) 	((x & 0b0000110000000000) >> 10)
# define BITS_10_14(x) 	((x & 0b0111110000000000) >> 10)
# define BITS_12_13(x) 	((x & 0b0011000000000000) >> 12)
# define BITS_14_15(x) 	((x & 0b1100000000000000) >> 14)

// control value of a bit
# define BIT_N(n, x) ( (x >> n) & 0x01 )
# define SETBIT(n, x) ( x |= 1 << n )
# define RESBIT(n, x) ( x &= ~(1 << n) )

# define FRAME_CYCLES    		70224

#endif // ! DEFINES_HPP
