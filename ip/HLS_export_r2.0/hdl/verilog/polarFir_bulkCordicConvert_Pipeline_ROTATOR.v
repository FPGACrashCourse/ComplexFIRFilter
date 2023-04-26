// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Version: 2022.2
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module polarFir_bulkCordicConvert_Pipeline_ROTATOR (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        select_ln68,
        select_ln68_1,
        sext_ln113,
        currentCos_V_out,
        currentCos_V_out_ap_vld,
        p_out,
        p_out_ap_vld
);

parameter    ap_ST_fsm_pp0_stage0 = 1'd1;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [23:0] select_ln68;
input  [23:0] select_ln68_1;
input  [13:0] sext_ln113;
output  [23:0] currentCos_V_out;
output   currentCos_V_out_ap_vld;
output  [23:0] p_out;
output   p_out_ap_vld;

reg ap_idle;
reg currentCos_V_out_ap_vld;
reg p_out_ap_vld;

(* fsm_encoding = "none" *) reg   [0:0] ap_CS_fsm;
wire    ap_CS_fsm_pp0_stage0;
wire    ap_enable_reg_pp0_iter0;
reg    ap_enable_reg_pp0_iter1;
reg    ap_enable_reg_pp0_iter2;
reg    ap_idle_pp0;
wire    ap_block_state1_pp0_stage0_iter0;
wire    ap_block_state2_pp0_stage0_iter1;
wire    ap_block_state3_pp0_stage0_iter2;
wire    ap_block_pp0_stage0_subdone;
wire   [0:0] icmp_ln113_fu_134_p2;
reg    ap_condition_exit_pp0_iter1_stage0;
wire    ap_loop_exit_ready;
reg    ap_ready_int;
wire   [5:0] cordicPhase_V_address0;
reg    cordicPhase_V_ce0;
wire   [11:0] cordicPhase_V_q0;
wire    ap_block_pp0_stage0_11001;
wire   [0:0] icmp_ln1649_fu_181_p2;
reg   [0:0] icmp_ln1649_reg_312;
wire   [23:0] currentCos_V_3_fu_211_p3;
reg   [23:0] currentCos_V_3_reg_322;
wire   [23:0] currentSin_V_3_fu_219_p3;
reg   [23:0] currentSin_V_3_reg_327;
wire   [63:0] zext_ln113_fu_152_p1;
wire    ap_block_pp0_stage0;
reg   [23:0] empty_fu_46;
wire   [23:0] select_ln1649_fu_251_p3;
wire  signed [23:0] sext_ln113_cast_fu_107_p1;
wire    ap_loop_init;
reg   [23:0] currentCos_V_fu_50;
reg   [23:0] ap_sig_allocacmp_currentCos_V_load;
reg   [23:0] currentSin_V_fu_54;
reg   [23:0] ap_sig_allocacmp_currentSin_V_load;
reg   [5:0] i_fu_58;
wire   [5:0] add_ln113_fu_140_p2;
wire    ap_block_pp0_stage0_01001;
wire   [4:0] trunc_ln1488_fu_157_p1;
wire   [23:0] trunc_ln1488cast_fu_161_p1;
wire   [23:0] trunc_ln1488cast9_fu_171_p1;
wire   [23:0] ashr_ln1488_1_fu_175_p2;
wire   [23:0] ashr_ln1488_fu_165_p2;
wire   [23:0] currentCos_V_1_fu_187_p2;
wire   [23:0] currentCos_V_2_fu_199_p2;
wire   [23:0] currentSin_V_1_fu_193_p2;
wire   [23:0] currentSin_V_2_fu_205_p2;
wire   [23:0] cordicPhase_V_load_cast_fu_235_p1;
wire   [23:0] add_ln813_fu_239_p2;
wire   [23:0] sub_ln813_fu_245_p2;
reg    ap_done_reg;
wire    ap_continue_int;
reg    ap_done_int;
reg   [0:0] ap_NS_fsm;
wire    ap_enable_pp0;
wire    ap_start_int;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 1'd1;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
#0 ap_enable_reg_pp0_iter2 = 1'b0;
#0 ap_done_reg = 1'b0;
end

polarFir_bulkCordicConvert_Pipeline_ROTATOR_cordicPhase_V_ROM_AUTO_1R #(
    .DataWidth( 12 ),
    .AddressRange( 64 ),
    .AddressWidth( 6 ))
cordicPhase_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(cordicPhase_V_address0),
    .ce0(cordicPhase_V_ce0),
    .q0(cordicPhase_V_q0)
);

polarFir_flow_control_loop_pipe_sequential_init flow_control_loop_pipe_sequential_init_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(ap_start),
    .ap_ready(ap_ready),
    .ap_done(ap_done),
    .ap_start_int(ap_start_int),
    .ap_loop_init(ap_loop_init),
    .ap_ready_int(ap_ready_int),
    .ap_loop_exit_ready(ap_condition_exit_pp0_iter1_stage0),
    .ap_loop_exit_done(ap_done_int),
    .ap_continue_int(ap_continue_int),
    .ap_done_int(ap_done_int)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_pp0_stage0;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_done_reg <= 1'b0;
    end else begin
        if ((ap_continue_int == 1'b1)) begin
            ap_done_reg <= 1'b0;
        end else if (((ap_loop_exit_ready == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            ap_done_reg <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if ((1'b1 == ap_condition_exit_pp0_iter1_stage0)) begin
            ap_enable_reg_pp0_iter1 <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            ap_enable_reg_pp0_iter1 <= ap_start_int;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter2 <= 1'b0;
    end else begin
        if ((1'b1 == ap_condition_exit_pp0_iter1_stage0)) begin
            ap_enable_reg_pp0_iter2 <= 1'b0;
        end else if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter2 <= ap_enable_reg_pp0_iter1;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b0 == ap_block_pp0_stage0_11001)) begin
        if (((1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
            currentCos_V_fu_50 <= select_ln68_1;
        end else if ((ap_enable_reg_pp0_iter2 == 1'b1)) begin
            currentCos_V_fu_50 <= currentCos_V_3_reg_322;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b0 == ap_block_pp0_stage0_11001)) begin
        if (((1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
            currentSin_V_fu_54 <= select_ln68;
        end else if ((ap_enable_reg_pp0_iter2 == 1'b1)) begin
            currentSin_V_fu_54 <= currentSin_V_3_reg_327;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b0 == ap_block_pp0_stage0_11001)) begin
        if (((1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
            empty_fu_46 <= sext_ln113_cast_fu_107_p1;
        end else if ((ap_enable_reg_pp0_iter2 == 1'b1)) begin
            empty_fu_46 <= select_ln1649_fu_251_p3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        if ((ap_loop_init == 1'b1)) begin
            i_fu_58 <= 6'd0;
        end else if (((icmp_ln113_fu_134_p2 == 1'd0) & (ap_enable_reg_pp0_iter1 == 1'b1))) begin
            i_fu_58 <= add_ln113_fu_140_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln113_fu_134_p2 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        currentCos_V_3_reg_322 <= currentCos_V_3_fu_211_p3;
        currentSin_V_3_reg_327 <= currentSin_V_3_fu_219_p3;
        icmp_ln1649_reg_312 <= icmp_ln1649_fu_181_p2;
    end
end

always @ (*) begin
    if (((icmp_ln113_fu_134_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_condition_exit_pp0_iter1_stage0 = 1'b1;
    end else begin
        ap_condition_exit_pp0_iter1_stage0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_loop_exit_ready == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_done_int = 1'b1;
    end else begin
        ap_done_int = ap_done_reg;
    end
end

always @ (*) begin
    if (((ap_idle_pp0 == 1'b1) & (ap_start_int == 1'b0) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b0))) begin
        ap_idle_pp0 = 1'b1;
    end else begin
        ap_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_ready_int = 1'b1;
    end else begin
        ap_ready_int = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter2 == 1'b1))) begin
        ap_sig_allocacmp_currentCos_V_load = currentCos_V_3_reg_322;
    end else begin
        ap_sig_allocacmp_currentCos_V_load = currentCos_V_fu_50;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter2 == 1'b1))) begin
        ap_sig_allocacmp_currentSin_V_load = currentSin_V_3_reg_327;
    end else begin
        ap_sig_allocacmp_currentSin_V_load = currentSin_V_fu_54;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        cordicPhase_V_ce0 = 1'b1;
    end else begin
        cordicPhase_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln113_fu_134_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        currentCos_V_out_ap_vld = 1'b1;
    end else begin
        currentCos_V_out_ap_vld = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln113_fu_134_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        p_out_ap_vld = 1'b1;
    end else begin
        p_out_ap_vld = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_pp0_stage0 : begin
            ap_NS_fsm = ap_ST_fsm_pp0_stage0;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln113_fu_140_p2 = (i_fu_58 + 6'd1);

assign add_ln813_fu_239_p2 = (empty_fu_46 + cordicPhase_V_load_cast_fu_235_p1);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd0];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_01001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_subdone = ~(1'b1 == 1'b1);

assign ap_block_state1_pp0_stage0_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state2_pp0_stage0_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state3_pp0_stage0_iter2 = ~(1'b1 == 1'b1);

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

assign ap_enable_reg_pp0_iter0 = ap_start_int;

assign ap_loop_exit_ready = ap_condition_exit_pp0_iter1_stage0;

assign ashr_ln1488_1_fu_175_p2 = $signed(ap_sig_allocacmp_currentSin_V_load) >>> trunc_ln1488cast9_fu_171_p1;

assign ashr_ln1488_fu_165_p2 = $signed(ap_sig_allocacmp_currentCos_V_load) >>> trunc_ln1488cast_fu_161_p1;

assign cordicPhase_V_address0 = zext_ln113_fu_152_p1;

assign cordicPhase_V_load_cast_fu_235_p1 = cordicPhase_V_q0;

assign currentCos_V_1_fu_187_p2 = (ashr_ln1488_1_fu_175_p2 + ap_sig_allocacmp_currentCos_V_load);

assign currentCos_V_2_fu_199_p2 = (ap_sig_allocacmp_currentCos_V_load - ashr_ln1488_1_fu_175_p2);

assign currentCos_V_3_fu_211_p3 = ((icmp_ln1649_fu_181_p2[0:0] == 1'b1) ? currentCos_V_1_fu_187_p2 : currentCos_V_2_fu_199_p2);

assign currentCos_V_out = currentCos_V_fu_50;

assign currentSin_V_1_fu_193_p2 = (ap_sig_allocacmp_currentSin_V_load - ashr_ln1488_fu_165_p2);

assign currentSin_V_2_fu_205_p2 = (ashr_ln1488_fu_165_p2 + ap_sig_allocacmp_currentSin_V_load);

assign currentSin_V_3_fu_219_p3 = ((icmp_ln1649_fu_181_p2[0:0] == 1'b1) ? currentSin_V_1_fu_193_p2 : currentSin_V_2_fu_205_p2);

assign icmp_ln113_fu_134_p2 = ((i_fu_58 == 6'd32) ? 1'b1 : 1'b0);

assign icmp_ln1649_fu_181_p2 = (($signed(ap_sig_allocacmp_currentSin_V_load) > $signed(24'd0)) ? 1'b1 : 1'b0);

assign p_out = empty_fu_46;

assign select_ln1649_fu_251_p3 = ((icmp_ln1649_reg_312[0:0] == 1'b1) ? add_ln813_fu_239_p2 : sub_ln813_fu_245_p2);

assign sext_ln113_cast_fu_107_p1 = $signed(sext_ln113);

assign sub_ln813_fu_245_p2 = (empty_fu_46 - cordicPhase_V_load_cast_fu_235_p1);

assign trunc_ln1488_fu_157_p1 = i_fu_58[4:0];

assign trunc_ln1488cast9_fu_171_p1 = trunc_ln1488_fu_157_p1;

assign trunc_ln1488cast_fu_161_p1 = trunc_ln1488_fu_157_p1;

assign zext_ln113_fu_152_p1 = i_fu_58;

endmodule //polarFir_bulkCordicConvert_Pipeline_ROTATOR
