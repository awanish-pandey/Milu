/*
Milu v3.0 - A Higher Order Mutation Testing Tool

Copyright (c) 2011, Yue Jia
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the University College London nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Mutator.h"
#include "ASTNodeUtil.h"
#include "ASTNode.h"

static gboolean mutator_milu_integer_constant_replacement_node_checking(ASTNode *);
static gboolean mutator_milu_integer_constant_replacement_clean(ASTNode * node, gint type);
static gboolean mutator_milu_integer_constant_replacement_mutate(ASTNode * node, gint type);

static ASTNode * tmp_mut_node = NULL;

Mutator * mutator_austin_milu_integer_constant_replacement()
{
	Mutator * mut = mutator_new("Arithmetic integer ", "");
	mut->node_checking = & mutator_milu_integer_constant_replacement_node_checking;
	mut->mutate = & mutator_milu_integer_constant_replacement_mutate;
	mut->clean = & mutator_milu_integer_constant_replacement_clean;
	mut->size = 6;
	return mut;
}


static gboolean mutator_milu_integer_constant_replacement_node_checking(ASTNode * node)
{
	if(is_ASTNode_kind_integer_literal(node))
		return TRUE;
	return FALSE;
}

static gboolean mutator_milu_integer_constant_replacement_mutate(ASTNode * node, gint type)
{
	switch(type)
	{

		case 1:
			tmp_mut_node = mutator_integer_constant_node_generator_for_austin_milu(node, "-1");
			return TRUE;
		case 2:
			tmp_mut_node = mutator_integer_constant_node_generator_for_austin_milu(node, "0");
			return TRUE;
		case 3:
			tmp_mut_node = mutator_integer_constant_node_generator_for_austin_milu(node, "1");
			return TRUE;
		case 4:
			tmp_mut_node = mutator_integer_constant_node_generator_for_austin_milu(node, g_strdup_printf("%d", atoi(node->text) + 1));
			return TRUE;
		case 5:
			tmp_mut_node = mutator_integer_constant_node_generator_for_austin_milu(node, g_strdup_printf("%d", atoi(node->text) - 1));
			return TRUE;
		case 6:
			tmp_mut_node = mutator_integer_constant_node_generator_for_austin_milu(node, g_strdup_printf("%d", atoi(node->text) * -1));
			return TRUE;
		default:
			break;
	}

	return FALSE;
}

static gboolean mutator_milu_integer_constant_replacement_clean(ASTNode * node, gint type)
{
	ASTNode_unlink (tmp_mut_node);
    ASTNode_free(tmp_mut_node);
	return TRUE;
}
